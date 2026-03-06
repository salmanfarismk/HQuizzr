# HQuizzr 🎴

A custom C++ flashcard app I built in the terminal to grind Japanese Hiragana and Romaji. It's completely modular, so you can throw whatever text-based flashcards you want into it, but it was born out of me wanting a fast, no-BS way to study without leaving the IDE. 

## Features
* **Saves Your Grind:** Automatically saves and loads your custom deck using a local `Hiragana.txt` file. 
* **Smart Grading:** Case-insensitive checking. If the answer is `ka`, the app accepts `ka`, `KA`, or `Ka` without yelling at you. 
* **Bulletproof CLI:** Wrote custom `std::cin` error handling. If you accidentally smash your keyboard and type letters into the number menu, the program catches it instead of crashing into an infinite loop.

## How to Run It
You just need a standard C++ compiler (like `g++`).