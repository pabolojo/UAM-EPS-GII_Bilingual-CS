from django.urls import path
from core import views

app_name = 'core'

# It creates a relation between the url and the view
urlpatterns = [
    path('', views.home, name='home'),
    path('login/', views.user_login, name='login'),
    path('logout/', views.user_logout, name='logout'),
    path('applygroup/', views.applygroup, name='applygroup'),
    path('applypair/', views.applypair, name='applypair'),
    path('convalidation/', views.convalidation, name='convalidation'),
]
