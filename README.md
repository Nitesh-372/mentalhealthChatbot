# Mental Health Chatbot

A simple C++ console chatbot that detects emotional themes in a user's message using keyword matching and replies with supportive text from local `.txt` files.

## Overview

This project is a rule-based mental health support chatbot. It reads a line of user input, compares the text against emotion keyword groups, and then prints a response based on the detected emotion and the number of matched keywords.

The chatbot is designed as a local console application and does not use any external APIs, databases, or machine learning models.

## How It Works

1. `main.cpp` loads emotion keywords from `emotions_detection.txt`.
2. The user types a message in the terminal.
3. The input is converted to lowercase.
4. The program checks whether any stored keywords appear in the input.
5. The emotion with the highest number of matches is selected.
6. A response is chosen:
   - `greetings` uses a random line from `Greetings.txt`
   - `listening` uses a random line from `listening.txt`
   - low-confidence matches use `Comfort.txt`
   - stronger matches print the full contents of the matching emotion response file

## Project Files

### Source and executable

- [main.cpp](C:/inetpub/mental%20health%20chatvot/main.cpp)  
  Main C++ source file for the chatbot.
- [main.exe](C:/inetpub/mental%20health%20chatvot/main.exe)  
  Compiled Windows executable already present in the repo.

### Keyword configuration

- [emotions_detection.txt](C:/inetpub/mental%20health%20chatvot/emotions_detection.txt)  
  Maps each emotion category to comma-separated keywords and phrases.

Current emotion groups found in this file:

- `greetings`
- `listening`
- `Sadness/Depression`
- `Anxiety/Fear`
- `Stress/Overwhelm`
- `Loneliness/isolation`
- `Anger/Frustration`
- `Shame/Guilt`
- `insecurity/Low Self-Worth`
- `Confusion/Hopelessness`
- `Emotional Numbness/Dissociation`

### Response text files

- [Greetings.txt](C:/inetpub/mental%20health%20chatvot/Greetings.txt)  
  Short greeting responses.
- [listening.txt](C:/inetpub/mental%20health%20chatvot/listening.txt)  
  Responses for users who mainly want to be heard.
- [Comfort.txt](C:/inetpub/mental%20health%20chatvot/Comfort.txt)  
  Intended for general comfort responses when only a small number of keywords match.
- [Sadness_Depression.txt](C:/inetpub/mental%20health%20chatvot/Sadness_Depression.txt)
- [Anger_Frustration.txt](C:/inetpub/mental%20health%20chatvot/Anger_Frustration.txt)
- [Anxiety_Fear.txt](C:/inetpub/mental%20health%20chatvot/Anxiety_Fear.txt)
- [Confusion_Hopelessness.txt](C:/inetpub/mental%20health%20chatvot/Confusion_Hopelessness.txt)
- [Shame_Guilt.txt](C:/inetpub/mental%20health%20chatvot/Shame_Guilt.txt)
- [Stress_Overwhelm.txt](C:/inetpub/mental%20health%20chatvot/Stress_Overwhelm.txt)
- [Loneliness_Isolation.txt](C:/inetpub/mental%20health%20chatvot/Loneliness_Isolation.txt)
- [Insecurity_LowSelfWorth.txt](C:/inetpub/mental%20health%20chatvot/Insecurity_LowSelfWorth.txt)
- [EmotionalNumbness_Dissociation.txt](C:/inetpub/mental%20health%20chatvot/EmotionalNumbness_Dissociation.txt)

### Editor configuration

- [.vscode/tasks.json](C:/inetpub/mental%20health%20chatvot/.vscode/tasks.json)  
  VS Code build task using MinGW `gcc.exe`.
- [.vscode/settings.json](C:/inetpub/mental%20health%20chatvot/.vscode/settings.json)  
  Disables C/C++ error squiggles in VS Code.

### Other document

- [ada_mentalhealthchatbot.docx](C:/inetpub/mental%20health%20chatvot/ada_mentalhealthchatbot.docx)  
  Project-related document included in the repository.

## Build

This project is set up for Windows and appears to use MinGW.

Example compile command:

```powershell
g++ main.cpp -o main.exe
```

If you want to use the included VS Code task, make sure MinGW is installed at:

```text
C:\MinGW\bin\
```

Note: the VS Code task currently calls `gcc.exe`. Since the source file is C++, `g++.exe` is typically the safer compiler choice.

## Run

Run the chatbot from the project folder so it can read the `.txt` files:

```powershell
.\main.exe
```

Example interaction:

```text
You:
I feel lonely and disconnected lately
Loneliness/isolation
3
...response text...
```

## Response Logic

- If the detected emotion is `greetings`, one random line is picked from `Greetings.txt`.
- If the detected emotion is `listening`, one random line is picked from `listening.txt`.
- If the highest keyword match count is `2` or less, the program tries to use `Comfort.txt`.
- If the match count is greater than `2`, the program prints the full contents of a specific emotion file for several supported emotions.
- If nothing suitable is found, it falls back to:

```text
Mental Health Bot 🤖: Take care of yourself. I'm always here if you need to talk.
```

## Important Notes and Current Limitations

- `Comfort.txt` is currently empty, so low-confidence matches may fall back to the default comfort message.
- `getComfortResponse()` expects `Comfort.txt` to contain lines in `emotion: response` format, but the current code calls it with `"Comfort.txt"` instead of an emotion name.
- Some emotion names are inconsistent between `emotions_detection.txt` and `main.cpp`:
  - `Loneliness/isolation` vs `Loneliness/Isolation`
  - `insecurity/Low Self-Worth` vs `Insecurity/LowSelfWorth`
- `Emotional Numbness/Dissociation` exists in the keyword file and has a response file, but `main.cpp` does not currently route to that file.
- The program seeds random selection inside `getRandomLineFromFile()`, which can repeat the same random result when called within the same second.
- The chatbot runs in an infinite loop and does not currently provide an `exit` or `quit` command.
- Matching is based on simple substring checks, so false positives can happen.
- This project provides supportive text only and is not a replacement for licensed mental health care or emergency help.

## Suggested Improvements

- Add an `exit` command.
- Fix emotion name mismatches.
- Add routing for `Emotional Numbness/Dissociation`.
- Fill `Comfort.txt` with properly formatted comfort responses.
- Seed randomness once in `main()` instead of on every file read.
- Avoid printing the raw detected emotion and match count in production mode.
- Replace substring matching with cleaner token-based matching.

## Requirements

- Windows
- A C++ compiler such as MinGW `g++`
- All `.txt` data files kept in the same folder as the executable

## Disclaimer

This chatbot is a learning project for emotional support conversations. It should not be used as a crisis-response system, diagnostic tool, or substitute for professional medical or psychological support.
# mentalhealthChatbot
