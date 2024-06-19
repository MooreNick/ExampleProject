from django.urls import path
from . import views

urlpatterns = [
    path("", views.home, name = "Home"),
    path("scores/", views.scores, name = "Scores")
]