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

The client will then show `What do you want to do?`

The server can execute 4 commands the client requests:
1. `add` to add a student to the database.
2. `display_all` to show all the students in the database.
3. `showscores`to show all the students whose score are greater than a desired number.
4. `delete` delete a student from the database.

Command line structure:

```shell
add [studentID] [firstName] [lastName] [score]
display_all none
display [score]
delete [studentID]
```

Examples:
```shell
add 291892 Francois Butter 86
display_all
showscores 75
delete 748393
```


## Licensing & Thanks

This project is released under the [MIT License][mit].

## Changelog

- v1.0.0

[mit]: ./LICENSE.txt
