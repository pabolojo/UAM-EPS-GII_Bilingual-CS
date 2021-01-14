from django.urls import reverse
from django.contrib.staticfiles import finders
from django.test import TestCase
from django.test import Client
from rango.models import Category, Page
from django.utils import timezone

class CategoryMethodTests(TestCase):
    def test_ensure_views_are_positive(self):
        """
        Ensures the number of views received for a Category are positive or zero.
        """
        category = add_category(name='test', views=-1, likes=0)
        self.assertEqual((category.views >= 0), True)

    def test_slug_line_creation(self):
        """
        Checks to make sure that when a category is created, an
        appropriate slug is created.
        Example: "Random Category String" should be "random-category-string".
        """
        category = add_category(name='Random Category String')
        self.assertEqual(category.slug, 'random-category-string')

def add_category(name, views=0, likes=0):
    category = Category.objects.get_or_create(name=name)[0]
    category.views = views
    category.likes = likes
    category.save()
    return category
    
class IndexViewTests(TestCase):
    def test_index_view_with_no_categories(self):
        """
        If no categories exist, the appropriate message should be displayed.
        """
        response = self.client.get(reverse('rango:index'))
        self.assertEqual(response.status_code, 200)
        self.assertContains(response, "There are no categories present")
        self.assertQuerysetEqual(response.context['categories'], [])

    def test_index_view_with_categories(self):
        """
        Checks whether categories are displayed correctly when present.
        """
        add_category('Python', 1, 1)
        add_category('C++', 1, 1)
        add_category('Erlang', 1, 1)
        response = self.client.get(reverse('rango:index'))
        self.assertEqual(response.status_code, 200)
        self.assertContains(response, "Python")
        self.assertContains(response, "C++")
        self.assertContains(response, "Erlang")
        num_categories = len(response.context['categories'])
        self.assertEquals(num_categories, 3)

class PageAccessTests(TestCase):
    def test_last_visit_future(self):
        """
        Checks if the last visit date of a page is in the future
        """
        category = add_category("Test Category")
        page = Page.objects.get_or_create(title="Test Page", category=category)[0]
        page.url = "www.google.es"
        page.save()
        self.assertTrue(page.last_visit < timezone.now())

    def test_last_visit_refresh(self):
        """
        Checks if the last visit is updated when we click on it
        """
        category = add_category("Test Category")
        page = Page.objects.get_or_create(title="Test Page", category=category)[0]
        page.url = "www.google.es"
        page.save()
        fecha_creacion = page.last_visit
        self.client.get(reverse('rango:goto'), {'page_id':page.id})
        page.refresh_from_db()
        self.assertTrue(fecha_creacion < page.last_visit)