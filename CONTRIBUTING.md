# Contributing
Thanks for Contributing

If you want to contribute:
1. Fork the project
2. Create new branch with your topic
3. Create pull-request

If you want to add a new package manager
1. Add it to `package_manager_list` in the `get_package_manager_list()` function in utils.cpp
2. Create a new statement inside packagemanager.cpp
### Squashing commits
You need to squash your commits!<br>
You can do it like this way:
```
git checkout YOUR_BRANCH
git rebase -i HEAD~n
# n is the number of your commits
# nano opens up. Edit all 'pick' to squash except the 'pick' on the first line.
# On the next screen you can edit commit messages
git push --force
```
