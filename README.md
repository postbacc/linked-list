# HW 1: Linked Lists

In this assignment you'll implement a linked list data
structure. We've covered the struct and associated operations in the
video lectures. Here's a summary:

* **init_node** - create a new node and return a pointer to it
* **report** - return a string representation of the list
* **append** and **append_data** - add to the end of the list
* **insert** and **insert_data** - insert into any spot in the list
* **size** - return the current size of the list
* **contains** - return true if the list contains a value

## Editing, Compiling and Testing

You only need to edit the `linked_list.cpp` implementation file, as
that is the only file that our official grading system will use.

After you've edited your implementation file, build it by running
`make` from a command line, or by having your editor run it for you
(though that's up to you to figure out if you want to go there.)

There are three ways to run the tests:

* `python grade.py linked_list_test` - this runs the python grading
  script, using `points.json` to tell it what the individual unit
  tests are, and how much they're worth. It tabulates your score with
  friendly colors.
* `./linked_list_test` - this runs all the unit tests in a row, and
  gives extremely verbose output.
* `./linked_list_test "[sometest]"` - runs a particular unit
  test. This gives verbose output for that specific test. The python
  script will give you a list of specific test names.

## Preconditions

### Pointers

In all cases, you can assume that a variable such as `node** top` has
these properties:

* `top` is not null.
* `*top` might be null.

Further, `node* head` might be null.

### Values

No restrictions on `int data` are provided - any value is acceptable.

### Offsets

It is the responsibility of calling contexts to ensure that offsets
are a reasonable value. For `remove`, there must be a node at the
given offset. For `insert`, the offset must be between 0 and `size()`
(inclusive).

If an unreasonable value is provided for an offset, your code should
just return without doing anything.

## Postconditions

Any function that modifies the structure of the linked list must
ensure the head pointer is correctly set before returning.
