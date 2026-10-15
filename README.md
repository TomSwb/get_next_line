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
* README.md

`Program version (in .programs/basic_version) additionally contains:`

* main.c
* test1.txt

##### Bonus version:

`Files:`

* get_next_line_bonus.c
* get_next_line_utils_bonus.c

`Additionally contains:`

* get_next_line_bonus.h

`Program version (in .programs/bonus_version) additionally contains:`

* main_bonus.c
* main_bonus.h
* main_utils_bonus.c
* test1.txt
* test2.txt
* test3.txt

## Instructions

#### Libft version:

Part of my libft. It can be added to it and used - see the instructions in my Libft README.

#### Program versions:

The test programs live in the hidden `.programs` folder. Each version folder contains its own copy of the get_next_line sources, so it can be compiled on its own.

Basic:

Compile (replace '42' with any positive number you choose):

```bash
cd .programs/basic_version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

Use (replace main.c with any single file you choose):

```bash
./a.out main.c
```

Bonus:

Compile (replace '42' with any positive number you choose):

```bash
cd .programs/bonus_version
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c main_utils_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

Use (replace main_bonus.c and test1.txt with any files you choose):

```bash
./a.out main_bonus.c test1.txt
```

Press Enter to see the next line. If you use the bonus version with multiple files, it first shows you each file's line 1, then each file's line 2, and so on, switching to the next file at each press.

Either reach the end of the file(s) or press CTRL + C to end the program.

Either version can also be used with stdin:

```bash
./a.out
```

After launching the program, write some text and press Enter. It will print your text back. Press CTRL + D to exit.

## Resources

#### Editor:

* `VSCodium`: Used to avoid Microsoft telemetry and AI-integrated temptations.

#### 42:

* `get_next_line.pdf` version: 14.3

#### Testing:

* [Tripouille's gnlTester](https://github.com/Tripouille/gnlTester): Used to test my implementation. It revealed the timeout on BUFFER_SIZE == 1 described below.

### AI:

⚠️ Disclaimer: I only ask for actual answers/solutions when I realise that I am missing theoretical knowledge, e.g., a new syntax or a new concept I had not explored before.

I always write my code to the best of my abilities first.

My AI agents are set to guide me with questions, as per the 42 pedagogical philosophy.

I use VSCodium on purpose to avoid AI integration. This means that, except for my copy-pastes into chats for some reviews, AI does not see my code, and AI never writes my code - I do not copy-paste from AI into my code.

`ChatGPT:`

1. Learning the theory, in particular static variables.

2. Peer-to-peer help, as I would get on campus.

3. Understanding pointers.

`Claude:`

1. Peer-to-peer help, as I would get on campus.

2. Checking for careless mistakes that could fail an evaluation, e.g., a .MD extension instead of .md.

3. Help in figuring out the need for PENDING_BUFFER and the logic to reduce the time needed with a small BUFFER_SIZE.

4. Help in completing and correcting this README.

## Detailed description:

### Why this algorithm:

#### Both basic and bonus versions:

I began by learning what a static variable is. I understood that it is a variable that stays in memory between function calls, until the program ends or is exited. I had, however, not understood that I needed to allocate its content. My first extract_buffer() was therefore not compliant, but it already had the structure it has now.

I found it important that get_next_line be mainly responsible for managing the overall operation and freeing data when required. This also helped me understand memory ownership more clearly, by deciding which function is responsible for each allocation and where that memory should be freed. It then became clear that I needed a way to extract the buffer into the static variable, to be able to work with it and find a line in it, as well as to save the leftover for the next call.

I therefore needed two main things: a buffer extractor and a line extractor.

`extract_buffer:`

In its first version, the function began by checking that a positive BUFFER_SIZE was given. It then allocated the buffer and read up to BUFFER_SIZE bytes into it. The buffer was then '\0'-terminated so it could be handled as a string. cat_buffer_data() would either copy the buffer into data if data == NULL, or concatenate it to the existing data.

get_next_line() calls extract_buffer() as many times as needed, until either data contains a '\n', indicating the end of a line, or reading == 0, which indicates the end of the file.

If this whole operation works as planned and either EOF or '\n' is detected, get_next_line() can then proceed by calling extract_line().

After testing with Tripouille's tester, I discovered that I had a timeout with BUFFER_SIZE == 1. With my implementation, reading a long line took over 4 seconds before data reached a '\n' and the line could be returned, while the tester times out after 1 second. I asked Claude for help on this one, as I was at home, and it made me realise that a concatenation was happening for every single byte read, which was why my program was slow. If I could ensure that the concatenation only happens once a '\n' is met or at EOF, it would be much faster.

Claude guided me in restructuring my functions. I also asked for help to make sure I respected the Norm, as it was 1am. The chosen strategy first removed the need for temp in the function, by relying on the concatenation function to free the previous data before transferring the pointer. That function could therefore return a success boolean instead of a string. Then the major changes came in extract_buffer(), introducing a loop based on the total number of bytes read, rather than on whether bytes were still being read. That total is compared to a new macro, PENDING_BUFFER, defined in the header with a size of 16384: 4 memory pages on most systems, and 1 memory page on systems with 16KB pages. From then on, the buffer is no longer erased and overwritten at each read: it is filled up until EOF is reached or the end of a line is detected inside it, and only then concatenated to data. Finally, PENDING_BUFFER is defined as a long (16384L) to avoid an int overflow, which would wrap around into a negative number when BUFFER_SIZE is close to INT_MAX (from INT_MAX - PENDING_BUFFER up to INT_MAX). It has to be a signed long rather than a size_t, because it is also compared to 'total', which is a signed ssize_t.

`extract_line:`

The extraction first determines the length needed for the line, using either '\n' or, if not found, '\0' as the end-of-line point, and allocates the required memory.

Once the allocation is done, it copies 'len' characters from data to line. It then calls clean_data().

`clean_data:`

This function moves the bytes remaining after the extracted line to the front of the data allocation. If no bytes remain except '\0', data is no longer needed and can be freed and reset to NULL.

#### Bonus version only:

The bonus version offers the challenge of reading from more than one file. My underlying goal was not to modify any of my utils, and to only use the 4 function slots still available in the GNL file to succeed. This was to avoid having two radically different versions.

I understood right away that my preferred approach would be a list of nodes, each containing the 'fd' as a recognisable key, a 'data' field to save the reading state of the corresponding fd, and obviously a 'next' pointing to the next node in the list.

I chose this because a struct gives me more flexibility and makes it easy to pass the different data points around to the helpers. A 'char **' could have been a possibility, but I thought it would have meant a more complex implementation, especially when a file is completed and its entry has to be removed from the array of pointers. Disconnecting and reconnecting nodes was a simpler picture to me.

After further research, I understood that this initial reasoning was partly wrong. I learned the main difference between the two possible implementations: a list allows any number of nodes, and therefore any number of files to be read, whereas an array of pointers is finite (even if that limit is large and can differ from system to system).

Also, an array of pointers requires allocating memory for that whole finite number of fds, whereas a list only requires memory for the files actually being read.

The trade-off is speed: a list requires going through up to 'n' nodes to find the corresponding fd, whereas a char ** gives direct access using the fd as an index. The clean-up of the list is also more complicated, as it requires relinking the nodes.

I had to change GNL itself to support this architecture, including finding the right node and freeing it when needed. Four additional helpers came out of it, but I did not need to change any of the other helpers.

`find_node`

find_node is what allows GNL to get the correct node pointer, giving it access to the corresponding data. If find_node finds that the fd does not have a node yet, it calls create_node() to create one and returns a pointer to the new node.

`create_node`

Creates and allocates a new node, storing the required 'fd' as its key.

`free_what_node`

When needed, GNL has to free both the data and the node. This function does the searching part of the job, then calls free_node(). It returns the result of the freeing (NULL).

`free_node`

Frees both the 'data' and the 'node' memory and returns NULL, making sure the list is left correctly linked, either to the previous node or to the head.