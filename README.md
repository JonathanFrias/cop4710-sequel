#COP4710 Sequel Engine (Seriously? WTF!)

This is a code repository to house our project. This project is totally
**open source**! (You should get over that because you want your name on
something *soooo* cool)

## Getting Started

1. Please sign up for a github account. (Many employers will expect you
   to have one anyway, so now's as good a time as any)
2. This uses a program called `git`, which is a version control system.
- It is ideally suited for code collaboration. Pretty much anyone who
  is anybody in the computing space uses this: [Exhibit A: The Linux
Kernel] (https://github.com/torvalds/linux)
3. Generally, the workflow for this type of system is to collaborate
   on code projects
4. Why use this? There are many reasons to use this, but to be concise,
   emailing code back and forth is wayy to tedious, error prone and also
wayy too common. I've also tried Dropboxing code with groups, which has
also caused a surprising amount of headaches.

I would like to retain a little bit more control of the codebase than
you guys, partially to review changes, but also because I think I
experience leading teams of developers, so please fork this repo instead
of making your own.

#####language: C

We are using the C programming language!

As such, we have a makefile to asist in compiling the code!

There are two makefile directives

`make test` and `make all`

Running `make test` will generate a executable binary at `out/test`
that runs our test functions.

Running `make all` will generate the rest of the source files into
an executable called `out/sql`.

## Proposed organizational Structure

We need to get on the same page with who is doing what. For this reason,
our first meeting should be about dividing up tasks as we see fit.

A sample list off the top of my head we can start with:

1. Parsing the sequel grammar (provided for us) into a data interchange
   format
2. A storage mechanism for records(tuples). This has many requirements
   that may be non-obvious.
3. The data definition language(Create/Drop table and all that)
4. Special wSelect queries - As far as the requirements for this project
   go, I understand that there is some versioning element to this. There
are some standard-ish software patterns to help us solve this problem.


We will define some common **functions** (using a header file) for each other
and treat them like *contracts*. These *contracts* with each other are for
to what kind of code we will write! This is awesome, because we know what
the method names will be and what they will return. Keep the madness to
a minimum.


## Proposed Workflow

- Basically fork this repo (this means copy the codebase in `git` world)
- Make changes
- Create a Pull Request (contains your changes) to be pulled into the
  mainline-codebase.
- this gives you a chance to understand who is contributing what
- If you have troubles with this procedure please contact me.
- Most of these operations can be done through the web interface
  (**worst** case scenario)
- There is tooling for using git. If you are not familiar I recommend
  [Github for Windows](https://desktop.github.com/) or [Github for Mac](https://desktop.github.com/)
