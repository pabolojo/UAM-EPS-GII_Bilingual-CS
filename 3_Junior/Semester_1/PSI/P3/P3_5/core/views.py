from django.shortcuts import render
from django.shortcuts import redirect
from django.urls import reverse

from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from core.models import (OtherConstraints, Pair, Student,
                         LabGroup)

from django.db.models import Q
from core.forms import PairForm, GroupForm
from datetime import date


def home(request):
    '''
    Method: home
    Description: View function to show the home page with the data of the
    logged user or a general data if any user is logged
    Input: Request object with the data of the user
    Output: Render object to build the template
    '''
    # If the user is logged we show his data
    if request.user.is_authenticated:
        context_dict = {}
        # It gets the student asociated to the user id of the logged user
        student = Student.objects.get(user_ptr_id=request.user.id)
        pair = Pair.objects.filter(Q(student1=student) | Q(student2=student))
        # It checks if the logged user has a pair and pass that information
        # to the render
        if len(pair) != 0:
            context_dict['pair'] = pair[0]
        else:
            context_dict['pair'] = None

        return render(request, 'home.html', context=context_dict)

    # If there isn't a logged user we send standar data
    return render(request, 'home.html')


def user_login(request):
    '''
    Method: user_login
    Description: View that manages the login of a user
    Input parameters: request object
    Return: Void
    '''
    context_dict = {}
    context_dict['wrong_login'] = False
    # If the request is a HTTP POST, try to pull out the relevant information.
    if request.method == 'POST':
        # Gather the username and password provided by the user.
        # This information is obtained from the login form.
        # We use request.POST.get('<variable>') as opposed
        # to request.POST['<variable>'], because the
        # request.POST.get('<variable>') returns None if the
        # value does not exist, while request.POST['<variable>']
        # will raise a KeyError exception.
        username = request.POST.get('username')
        password = request.POST.get('password')
        # Use Django's machinery to attempt to see if the username/password
        # combination is valid - a User object is returned if it is.
        user = authenticate(username=username, password=password)
        # If we have a User object, the details are correct.
        # If None (Python's way of representing the absence of a value),
        # no user with matching credentials was found.
        if user:
            login(request, user)
            return redirect(reverse('core:home'))
        else:
            # Bad login details were provided. So we can't log the user in.
            context_dict['wrong_login'] = True
            return render(request, 'login.html',
                          context=context_dict)
    # The request is not a HTTP POST, so display the login form.
    # This scenario would most likely be a HTTP GET.
    else:
        # No context variables to pass to the template system, hence the
        # blank dictionary object...
        return render(request, 'login.html', context=context_dict)


@login_required
def user_logout(request):
    '''
    Method: logout
    Description: logs out the logged user
    Input: Request object with the data of the user
    Output: Render object to build the template
    '''
    logout(request)
    return render(request, 'logout.html')


@login_required
def applygroup(request):
    '''
    Method: applygroup
    Description: View that manages when a user tries to apply to a group
    Input parameters: request object
    Return: Void
    '''
    context_dict = {}
    context_dict['date'] = False

    # we check that the start date is not in the future
    if OtherConstraints.objects.all()[0].selectGroupStartDate > date.today():
        return render(request, 'applygroup.html', context=context_dict)

    # if the start date is in the past, we set the context flag date to true
    context_dict['date'] = True

    # we get the students object of the user logged in and the pair
    # that it belongs to, if any
    user = Student.objects.get(user_ptr_id=request.user.id)
    pair = Pair.objects.filter((Q(student1=user) |
                                Q(student2=user)) & Q(validated=True))
    context_dict['group_form'] = GroupForm(user=user)
    context_dict['group_user'] = user.labGroup

    # if the user does no tbelong to any group
    if user.labGroup is None:
        # if the method is a POST
        if request.method == 'POST':
            # get the group requested by the user
            form = GroupForm(user=user, data=request.POST)
            # check that the group is a valid one
            if form.is_valid():
                group = LabGroup.objects.get(id=request.POST.get('labId'))
                context_dict['group_user'] = group
                # if the user has no partner, add it to
                # the labgroup and encrease the counter
                if len(pair) == 0:
                    group.counter = group.counter + 1
                    user.labGroup = group
                    user.save()
                    group.save()
                # if the user has a partner, add both components of
                # the pair to that labgroup
                # and increase the counter by 2
                else:
                    group.counter = group.counter + 2
                    pair[0].student1.labGroup = group
                    pair[0].student2.labGroup = group
                    pair[0].student1.save()
                    pair[0].student2.save()
                    group.save()

    return render(request, 'applygroup.html', context=context_dict)


@login_required
def applypair(request):
    '''
    Method: applypair
    Description: View function to show the status of the pair
    aplication of the logged user
    Input: Request object with the data of the user
    Output: Render object to build the template
    '''
    context_dict = {}
    context_dict['pair_form'] = PairForm(user=request.user)
    user = Student.objects.get(user_ptr_id=request.user.id)

    pair = Pair.objects.filter(Q(student1=user))
    context_dict['pair_user'] = None

    # We check if the logged user has already requested a pair
    if len(pair) == 0:
        if request.method == 'POST':
            form = PairForm(user=user, data=request.POST)
            # If he has not requested a pair we get the data
            # of the student that he sends in the form
            if form.is_valid():
                student = Student.objects.get(
                    user_ptr_id=request.POST.get('student2'))
                # We check if the student that he selected has also requested
                # to be apaired with him
                pairs = Pair.objects.filter(Q(student1=student) &
                                            Q(student2=user) &
                                            Q(validated=False))
                # If that's not the case we store the request
                if len(pairs) == 0:
                    p = Pair.objects.get_or_create(
                        student1=user, student2=student)[0]
                    p.save()
                    context_dict['pair_user'] = p
                # If it is the case we validate the pair and save the data
                else:
                    pairs[0].validated = True
                    pairs[0].save()
                    context_dict['pair_user'] = pairs[0]

    # If has already requested a pair, we show him the pair he
    # has already requested
    else:
        context_dict['pair_user'] = pair[0]

    return render(request, 'applypair.html', context=context_dict)


@login_required
def convalidation(request):
    '''
    Method: convalidation
    Description: View function to show the status of Lab convalidation
    of the logged user
    Input: Request object with the data of the user
    Output: Render object to build the template
    '''
    context_dict = {}
    student = Student.objects.get(user_ptr_id=request.user.id)

    # We check if the user is in a validated pair
    context_dict['pair'] = len(Pair.objects.filter(
        (Q(student1=student) | Q(student2=student)) & Q(validated=True)))
    context_dict['conv'] = None

    # If is not in a pair, we check the requeriments
    if context_dict['pair'] == 0:
        context_dict['conv'] = False
        if (OtherConstraints.objects.all()[0].minGradeTheoryConv <=
            student.gradeTheoryLastYear and
            OtherConstraints.objects.all()[0].minGradeLabConv <=
                student.gradeLabLastYear):
            context_dict['conv'] = True
            student.convalidationGranted = True
            student.save()

    # If is part of a validated pair we show the information (conv = None)
    # If not, we show if he has the requeriments (conv = True)
    # or if not (conv = False)
    return render(request, 'convalidation.html', context=context_dict)


