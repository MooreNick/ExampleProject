from django.shortcuts import render, HttpResponse
from .models import gameResults
import pandas as pd

# Create your views here.

def home(request):
    return render(request, "home.html")

def scores(request):
    data = pd.read_csv("gs://example_educational_bucket/scores.csv")
    for i in range(len(data)):
        gameResults.objects.create(name = data['name'][i], score = data['score'][i])

    displayScores = gameResults.objects.all()

    return render(request, "scores.html", {"scores" : displayScores})