*This project has been created as part of the 42 curriculum by [tschwab](https://profile-v3.intra.42.fr/users/tschwab)*

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

`Program version additionally contains (in .extra):`

* main.c
* test1.txt
* a.out

##### Bonus version:

`Files:`

* get_next_line_bonus.c
* get_next_line_utils_bonus.c

`Additionally contains:`

* get_next_line_bonus.h

`Program version additionally contains (in .extra):`

* main_bonus.c
* main_utils_bonus.c
* test1.txt
* test2.txt
* test3.txt
* a.out

## Instructions

#### Libft version: 
Part of my libft. It can be added to it and used - see instructions in the Libft README 

#### Program versions:

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

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c main_utils_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c

```

Use (replace main.c and text.txt with any files you choose):

```bash

./a.out main.c text.txt

```

Press Enter to see the next line. If using the bonus version with multiple files, it will first show you each file's line 1, then each file's line 2, etc., changing which files it is working with at each press.

Either reach the end of the file(s) or press CTRL + C to end the program.

Either version can be used with stdin:

```bash

./a.out

```

After launching the program, write some text and then press Enter. It will print your text back. Press CTRL + D to exit.

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

`ChatGPT:`

1. Understanding of static variables.

2. Peer-to-peer help as I would get on campus.

3. Pointer understanding.

`Claude:`

1. Peer-to-peer help as I would get on campus.

2. Stupid mistake check to avoid failing moulinette because e.g. I used .MD extension instead of .md

3. Help in figuring out the need for PENDING_BUFFER and the logic to reduce time needs for a small BUFFER_SIZE

## Detailed description:

#### Why this algorithm:

#### Both basic and bonus versions:

I began by learning what a static variable is. I understood that it is a variable that stays in memory between function calls, until the program ends or is exited. I had, however, not understood that I needed to allocate its content. My first extract_buffer() was therefore not compliant, but already had the structure it has now.

I found it important that get_next_line be mainly responsible for managing the overall operation and freeing data if required. This also helped me understand memory ownership more clearly, by deciding which function is responsible for each allocation and where that memory should be freed. Then it became clear that I needed a way to extract the buffer into the static variable to be able to work with it and find a line in it, as well as save the leftover for the next call.

I therefore needed two main things: a buffer extractor and a line extractor.

`extract_buffer:`

The function begins by checking if a positive BUFFER_SIZE was given. It then allocates the buffer and reads up to BUFFER_SIZE bytes into it. The buffer is then '\0' terminated so it can be handled as a string. cat_buffer_data() will either copy the buffer into data if data == NULL, or concatenate it to the existing data.

get_next_line() will call extract_buffer() as many times as needed, until either data contains a '\n', indicating the end of a line, or reading == 0, which indicates the end of the file.

If this whole operation works as planned and either EOF or '\n' is detected, get_next_line() can then proceed by calling extract_line.

After testing with Tripouille, I discover that I had a timeout on BUFFER_SIZE == 1. This because with my implementation, it was taking over 4" for the read to complete and data to reach a '\n' before returnning when it came to test long lines and Tripouilles times out at 1". I asked Claude for help on this one as I was home and it made me realise that concatenation was happening for every single byte and that was the reason that my program was slow, if could ensure that concatenation happens only once we met a '\n' or at eof, then it would be much faster.

Claude guided me in recomposing my functions. I asked for help to ensure I respect the norm and it was also 1am. The chosen strategy relied first on removing the need for temp in the function and relying on the concatenation function to free the previous data before transfering the pointer. That function could therefore return a success boolean instead of an array. Then the major changes came into extract_buffer, introducing a loop based on the total of bytes read and not anymore on if a byte was still being read. That total is compared to a new macro, PENDING_BUFFER that i defined in the include with a size of 16384L, classic 4 memory pages for most system and 1 memory page for 16KB system. From then on, the buffer is not anymore and erase over, but is in itself concatenate until we reach the eof or am end of a line is detected inside the buffer. Finally PENDING_BUFFER is define as a long to avoid overflows and turn around of int into a negative number when using BUFFER_SIZE INT_MAX up to INT_MAX - PENDING_BUFFER - 1.

`extract_line:`

The extraction will first determine the length needed for the line, using either '\n' or, if not found, '\0' as the end-of-line point, and allocate the required memory.

Once the allocation is done, it copies 'len' characters from data to line. It then calls clean_data().

`clean_data:`

This function moves the bytes remaining after the extracted line to the front of the data allocation. If no bytes remain except '\0', data is no longer needed and can be freed and reset to NULL.

#### Bonus version only:

The bonus version offers the challenge of being able to read from more than one file. My underlying goal was to not modify any of my utils and only use the available 4 function slots in the GNL file to succeed. This was to avoid having two radically different versions.

I understood right away that my preferred approach would be through a list of nodes, each containing the 'fd' as a recognisable key, a 'data' field allowing me to save the corresponding 'fd' data status, and obviously a 'next' pointing to the next node in the list.

I chose this because being a struct allows me more flexibility and an easiness of passing around the different data point into the helpers. A 'char **' could have been a possibility, but would have meant a more complex implementation especially around the completion of a file and therefore the need to remove that line from the overall array of pointers. To disconnect and reconnect nodes was a simpler picture to me. 

After further research I understood that this initial reason was partly wrong. I learned the main difference between both possible implementations: a list allows for any amount of node and therefore any amount of files to be read, when an array of pointers is finite (even if that limit is large and can differ from system to system). 

Also an array of pointers would require to allocate the memory for that finite size of fd pointers required, when a list is only requiring to allocate the memory for the actual amount of files.

The trade-of is speed, as a list requires to go through potential 'n' nodes to find the corresponding fd when a char ** search using the fd as index. The clean-up of the list is also more complicated requiring to relink the nodes.

I had to change GNL itself to support that architecture, including finding the right node and freeing it when needed. Four additional helpers came out of it. But I did not need to change any of the other helpers.

`find_node`

find_node is what allows GNL to get the correct node pointer, giving it access to the corresponding data. If find_node finds that the fd does not have a node, it calls create_node() to create one and returns a pointer to the new node.

`create_node`

Creates and allocates a new node, placing the required 'fd' as its key.

`free_what_node`

When needed, GNL needs to free both the data and the node. This function does the search part of the job, then calls free_node(). It returns the result of freeing (NULL).

`free_node`

Frees both the 'data' and 'node' memory, returning NULL, ensuring the list is left correctly linked, either to the previous node, or to the head.
