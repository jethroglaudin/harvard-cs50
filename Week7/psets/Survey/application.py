import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    name = request.form.get("name")
    email = request.form.get("email")
    brand = request.form.get("brand")
    carrier = request.form.get("carrier")
    satisfied = request.form.get("satisfied")
    switch = request.form.get("switch")
    if not name or not email or not brand or not carrier or not satisfied or not switch:
        return render_template("error.html", message="You are missing some fields. Please go back.")

    file = open("survey.csv", "a")
    writer = csv.writer(file)
    writer.writerow((name, email, brand, carrier, satisfied, switch))
    file.close()
    return redirect('/sheet')


@app.route("/sheet", methods=["GET"])
def get_sheet():
    file = open("survey.csv", "r")
    reader = csv.reader(file)
    consumers = list(reader)
    return render_template("sheet.html", consumers=consumers)
