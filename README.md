# Electronic Wallet System
This repository contains a C++ project developed as part of a university assignment.

## The goal
The objective is to create an electronic wallet system implemented in C++ with bidirectional data flow between two programs.

## How to compile

A build.bat file is included to compile both programs automatically. To use it, ***make sure you have g++ installed and are running on Windows.***

## How it works
The programs are operated via the command line using arguments. Each program supports the `--help` option to display all available commands.
Once the executables are built, open the containing directory in a terminal and run them using:
```
./<app_name>.exe <commands>
```
The system uses a `cards.csv` file to store all wallet cards and a `transactions.txt` file to log all actions in chronological order.
