# TCP Client/Server Project

Authors: Kevin Funderburg

<details>
  <summary><strong>Table of Contents</strong> (click to expand)</summary>
<!-- TOC depthFrom:2 -->

- [About](#about)
- [Usage](#usage)
- [Licensing & Thanks](#licensing--thanks)
- [Changelog](#changelog)

<!-- /TOC -->
</details>

## About
The goal of this project is to gain a fundamental understanding of the interactions between clients and servers via TCP. This is shown through development of a school database system, where clients can make requests to a server, the server then processes the requests and returns the results.

## Usage
Make commands
```shell
make
make clean
```
Once compiled, begin the server with `./server` and the client with `.client`.

The client will then show `What would you like to do? (enter h for help) :`

### Command line structure:

```shell
[adasdeh] [a add] [da delete_all] [s showscores] [d delete] [e exit] [h help]

a add
    adds a student to the database with the following parameters:
    [student ID] [First Name] [Last Name] [Grade]
da display_all
    display all student data in database
s showscores
    show all students with a grade higher than [grade]
d delete
    delete a student from data base with student ID = [student ID]
e exit
    exit the application
h help
    outputs usage listing

```

### Examples:
```shell
a 291892 Francois Butter 86
da
showscores 75
delete 748393
```


## Licensing & Thanks

This project is released under the [MIT License][mit].

## Changelog

- v1.0.0

[mit]: ./LICENSE.txt
