*This project has been created as part of the 42 curriculum by \<tschwab>*

# get_next_line - a function by TomSwb

## Description

#### Goal:

Create my own line-by-line reading function.

#### Brief overview:

##### Basic version:

`Files:`

* get_next_line.c
* get_next_line_utils.c

`Additionally contains:`

* get_next_line.h
* README

TODO []:

##### Bonus version:

`Files:`

* get_next_line_bonus.c
* get_next_line_utils_bonus.c

`Additionally contains:`

* get_next_line_bonus.h

## Instructions

`Libft version:` Part of my libft. It can be added to it and used (currently only basic version is ready).

`Program version:`

````
Basic:

Compile (replace '42' with any positive number you choose):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

Use (replace main.c with any single file you choose):

```bash
./a.out main.c
```

Bonus:

Compile (replace '42' with any positive number you choose):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

Use (replace main.c and text.txt with any files you choose):

```bash
./a.out main.c text.txt
```
````

Press Enter to see the next line. If using the bonus version with multiple files, it will first show you each file's line 1, then each file's line 2, etc., changing which files it is working with at each press.

Either reach the end of the file(s) or press CTRL + C to end the program.


Either version can be used with stdin:

```bash
./a.out
```

After launching program, writes some text then press enter, it will print you text again.

## Resources

#### Editor:

* `VSCodium`: Used to avoid Microsoft telemetry and AI-integrated temptations.

#### 42:

* `get_next_line.pdf` version: 14.3

### AI:

#### Before beginning of cursus

⚠️ Disclaimer: I only ask for actual answers/solutions when I realise that I am missing theoretical knowledge.

e.g.: a new syntax or a new concept I had not explored previously.

I always write my code to the best of my abilities first.

My AI agents are set to guide me with questions as per the 42 pedagogical philosophy.

I use VSCodium on purpose to not have AI integration. This means that, except for my copy-pastes into chats for some reviews, AI does not see my code, and AI will never write my code - I do not copy-paste from AI into my code.

* `ChatGPT`:

  1. Understanding of static variables.
  2. Peer-to-peer help as I would get on campus.
  3. Pointer understanding.

## Detailed description:

#### Why this algorithm:

I began by learning what a static variable is. I understood it is a variable that stays in memory between function calls, until the program ends or is exited. I had, however, not understood that I needed to allocate its content. My first extract_buffer was therefore not compliant but already had the structure it has now.

I found it important that get_next_line be mainly responsible for managing the overall operation and the freeing of data if required. This also helped me understand memory ownership more clearly, by deciding which function is responsible for each allocation and where that memory should be freed. Then it became clear I needed a way to extract the buffer into the static variable to be able to work with it and find a line in it, as well as save the leftover for the next call.

I therefore needed two main things: a buffer extractor and a line extractor.

`ft_extract_buffer:`

The function begins by checking if a positive BUFFER_SIZE was given. It then allocates the buffer and reads up to BUFFER_SIZE bytes into it. The buffer is then '\0' terminated so it can be handled as a string. ft_strcat will either copy the buffer into data if data == NULL, or concatenate it to the existing data.

get_next_line will call ft_extract_buffer as many times as needed, until either data contains a '\n', indicating the end of a line, or reading == 0, which indicates the end of the file.

If this whole operation works as planned and either EOF or '\n' is detected, get_next_line can then proceed by calling ft_extract_line.

`ft_extract_line:`

The extraction will first determine the length needed for the line, using either '\n' or, if not found, '\0' as the end-of-line point, and allocate the required memory.

Once the allocation is done, it copies 'len' characters from data to line. It then calls ft_clean_data.

`ft_clean_data:`

This function moves the bytes remaining after the extracted line to the front of the data allocation. If no bytes remain except '\0', data is no longer needed and can be freed and reset to NULL.
