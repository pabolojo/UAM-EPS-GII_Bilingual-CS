# Generated by Django 2.2.5 on 2020-11-08 11:24

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('core', '0006_auto_20201108_1123'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='student',
            options={'ordering': ('last_name', 'first_name')},
        ),
    ]
