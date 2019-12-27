import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get amount of user's cash to display
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])


    # Get the stocks that the user owns

    portfolio = db.execute("SELECT stock_symbol, stock_name, share_price, shares, date_purchased FROM users_portfolio WHERE user_id = :user_id", user_id = session["user_id"])

    # look up current stock price based on what shares of stocks the user owns


    full_portfolio = {}

    for stock in portfolio:
        symbol = stock["stock_symbol"]
        shares = stock["shares"]
        quote = lookup(symbol)
        price = float(quote["price"])
        full_portfolio[stock["stock_symbol"]] = {"price": price, "total": price * shares}

    # print(full_portfolio)
    # print(portfolio)

    cash_balance = cash[0]["cash"]

    return render_template("index.html", portfolio = portfolio, full_portfolio = full_portfolio, cash_balance = cash_balance)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    symbol = request.form.get("symbol")
    shares = request.form.get("shares", type=int)


    if request.method == "POST":
        if not symbol:
            return apology("Must enter stock", 400)
        if not shares:
            return apology("Must enter amount of shares", 400)
        if shares <= 0:
            return apology("Invalid Number")

        ## GET stock data
        stock_data = lookup(symbol)

        # Validate if the symbol inputted exists
        if not stock_data:
            return apology("Stock could not be found", 400)


        # Get current user's total cassh
        rows = db.execute("SELECT cash From users Where id = :user_id", user_id = session['user_id'])[0]

        user_cash = int(rows['cash'])

        # Stock Symbol
        stock_symbol = stock_data["symbol"]

        # Stock Name
        stock_name = stock_data["name"]

        # share price of the stock
        share_price = stock_data["price"]

        # calculate the total cost for shares
        # share price * Amt of shares
        total_cost = share_price * shares

        # check to see if user has enough money to complete transaction

        if total_cost > user_cash:
            return apology("Insufficient funds")

        ## should it pass continue with storing

        user_balance = user_cash - total_cost
        # update user's cash within users database

        db.execute("UPDATE users Set cash = :user_balance Where id = :user_id", user_balance=user_balance,
                  user_id=session['user_id'])

        stock = db.execute("SELECT shares as portfolio_shares FROM users_portfolio WHERE user_id = :user_id AND stock_symbol = :stock_symbol", user_id = session["user_id"], stock_symbol = stock_symbol)[0]


        if not stock:
            # write user's stock purchases into users_portfolio
            db.execute("INSERT INTO users_portfolio (user_id, stock_symbol, stock_name, share_price, shares, date_purchased) Values (:user_id, :stock_symbol, :stock_name, :share_price, :shares, :date_purchased)",
                       user_id = session["user_id"],
                       stock_symbol = stock_symbol,
                       stock_name = stock_name,
                       share_price = share_price,
                       shares = shares,
                       date_purchased = timestamp)


        else:

            db.execute("UPDATE users_portfolio SET shares = :updated_shares WHERE user_id = :user_id AND stock_symbol = :stock_symbol",
                        user_id = session['user_id'],
                        stock_symbol = stock_symbol,
                        updated_shares = int(stock['portfolio_shares']) + shares)

            # print(stock[0]["portfolio_shares"])

            # note this transcation in user's history

        buy_transaction = f"Bought {shares} shares of {stock_name}({stock_symbol})"
        db.execute("INSERT INTO history (user_id, stock_symbol, shares, transaction_date, portfolio_transaction) VALUES (:user_id, :stock_symbol, :shares, :transaction_date, :portfolio_transaction)",
                  user_id = session['user_id'],
                  stock_symbol = stock_symbol,
                  shares = int(stock['portfolio_shares']) + shares,
                  transaction_date = timestamp,
                  portfolio_transaction = buy_transaction)

        flash(f"Congrats you purchased ${shares} shares of {stock_name}")

        total = usd(total_cost)
        balance = usd(user_balance)

        return render_template("buy.html", total=total, balance=balance)

    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username = request.args.get("username")

    user = db.execute("SELECT username FROM users WHERE username = :username", username=username)

    if len(user) < 1 and username != user:
        return jsonify(True)
    else:
        return jsonify(False)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT stock_symbol, shares, transaction_date, portfolio_transaction FROM history WHERE user_id = :user_id ORDER BY transaction_date",
                              user_id = session["user_id"])

    if transactions:
        return render_template("history.html", transactions = transactions)

    else:
        return apology("No transactions")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    symbol = request.form.get("symbol")
    if request.method == "POST":
        if not symbol:
            return apology("Please Enter Stock Symbol", 400)

        quote = lookup(symbol)

        # Validate if the symbol inputted exists
        if not quote:
            return apology("Stock could not be found", 400)

        if quote:
           return render_template("quoted.html", stock_name = quote["name"], stock_price = usd(quote["price"]), stock_symbol = quote["symbol"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    ## request user's name, username, password,
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    #forget any user_id
    session.clear()

    if request.method =="POST":
        # For checking if username was submitted
        if not username:
            return apology("must provide username")
        # Checking if password was submitted
        elif not password:
            return apology("must provide password")
        # Checking if user typed in confirm password
        elif not confirmation:
            return apology("must confirm password")
        # Checking if password matches the confirmed password
        elif password != confirmation:
            return apology("password must be identical")

        # Hash user password before we store into SQL DB
        hash = generate_password_hash(password)

        # input user into DB
        #Query database for usernames
        exist = db.execute("SELECT username FROM users Where username = :username",
                            username=username)

        # if exist is true that means there is already a username that exists
        if exist:
            return apology("username already exists")

        # if not, then the username is able to be used and proceed to inserting the values
        if not exist:
            db.execute("INSERT INTO users (username, hash) Values (:username, :hash)",
                              username=username, hash=hash)

        user_id = db.execute("SELECT id FROM users Where username = :username", username=username)

        session["user_id"] = user_id[0]["id"]
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if request.method == "POST":

        # Make sure user inputs symbol
        if not symbol:
            return apology("Please enter stock")

        symbol_check = lookup(symbol)

        if symbol_check == None:
            return apology("Stock does not exist")

        # check shares
        if not shares or int(shares) < 1:
            return apology("Please enter a value greater than 1")

        stock_name = symbol_check["name"]


        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        user_cash = cash[0]["cash"]
        print(user_cash)

        user_stocks = db.execute("SELECT SUM(shares) as portfolio_shares FROM users_portfolio WHERE user_id = :user_id AND stock_symbol = :stock_symbol GROUP BY stock_symbol",
                                    user_id=session["user_id"], stock_symbol = symbol)

        print(user_stocks)

        # check to make sure user has enough shares left to sell
        if len(user_stocks) != 1 or user_stocks[0]["portfolio_shares"] < int(shares):
            return apology("You do not have enough shares to sell")

        current_share_price = symbol_check["price"]

        sell_total = current_share_price * int(shares)

        # after we get the sell total value we must update user's cash currently

        db.execute("UPDATE users SET cash = cash + :sell_total WHERE id = :user_id", user_id = session["user_id"], sell_total = sell_total)

        # next update user's portfolio changing the amount of shares


        new_shares = int(shares)


        db.execute("UPDATE users_portfolio SET shares = shares - :new_shares WHERE user_id = :user_id AND stock_symbol = :stock_symbol",
                   user_id = session["user_id"],
                   stock_symbol = symbol,
                   new_shares = new_shares)

        shares_history = user_stocks[0]["portfolio_shares"] - new_shares

        sold_transaction = f"Sold {shares} share(s) of {stock_name}({symbol})"
        db.execute("INSERT INTO history (user_id, stock_symbol, shares, transaction_date, portfolio_transaction) VALUES (:user_id, :stock_symbol, :shares, :transaction_date, :portfolio_transaction)",
                  user_id = session["user_id"],
                  stock_symbol = symbol,
                  shares = shares_history,
                  transaction_date = timestamp,
                  portfolio_transaction = sold_transaction)

        flash(f"You've sold {shares} share(s) of {symbol_check['name']}")


    return render_template("sell.html")

@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    if request.method == "POST":
        deposit = int(request.form.get("deposit"))

        if not deposit:
            return apology("Please Enter Amount You Want Deposited")

        updated_cash = deposit

        db.execute("UPDATE users SET cash = cash + :updated_cash WHERE id = :user_id", user_id = session["user_id"], updated_cash = updated_cash)
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
        flash(f"We've received your deposit of ${deposit}! ")
        balance = int(cash[0]["cash"])
        flash(f"Your Balance now stands at ${balance}")

    return render_template("deposit.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
