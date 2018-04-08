#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "linked_list.h"
#include <string>

using namespace std;

node* build_three_node_list(int one, int two, int three) {
  node* top = new node;
  top->data = one;
  top->next = new node;
  top->next->data = two;
  top->next->next = new node;
  top->next->next->data = three;
  top->next->next->next = NULL;
  return top;
}

node* scan(node* top, int how_many) {
  int count = 0;
  node* cursor;
  for (cursor = top; count < how_many && cursor != NULL; cursor = cursor->next) {
    count++;
  }
  return cursor;
}

bool expect_all(int vals[], int size, node** top) {
  bool ret = true;
  node* cursor = *top;
  for (int i=0; i < size; i++) {
    if (cursor == NULL || cursor->data != vals[i]) {
      if (cursor == NULL) {
        cout << "Cursor became null." << endl;
      } else if (cursor->data != vals[i]) {
        cout << cursor->data << " != " << vals[i] << endl;
      }
      ret = false;
      break;
    }
    cursor = cursor->next;
  }
  return ret;
}

TEST_CASE("Linked lists: initialization", "[init]" ) {
  node* root = init_node(42);
  REQUIRE(root != NULL);
  REQUIRE(root->data == 42);
  REQUIRE(root->next == NULL);
}

TEST_CASE("Linked lists: report", "[report]") {
  node* top = NULL; // empty list
  string exp ("");
  string out = report(top);
  REQUIRE(string::npos != out.find(exp, 0));
  top = build_three_node_list(1, 2, 3);
  exp = "1 2 3";
  out = report(top);
  REQUIRE(string::npos != out.find(exp, 0));
}

TEST_CASE("Linked lists: append data", "[append data]") {
  node* top = build_three_node_list(42, 74, 51);
  append_data(&top, 10);
  node* four = scan(top, 3);
  REQUIRE(four != NULL);
  REQUIRE(four->data == 10);
  append_data(&top, 99);
  node* five = scan(top, 4);
  REQUIRE(five != NULL);
  REQUIRE(five->data == 99);
}

TEST_CASE("Linked lists: append node", "[append node]") {
  node* head = NULL;
  node** top = &head;
  
  // test appending to empty list
  node* ap_seven = init_node(7);
  append(top, ap_seven); // add node 7 to an empty list
  REQUIRE(*top != NULL); // ensure the list has a non-null head
  node* erst = scan(*top, 0); // get the first element in the list
  REQUIRE(erst != NULL); // ensure first element isn't null
  REQUIRE(erst == ap_seven); // ensure first element is the ap_seven node
  REQUIRE(erst->data == 7); // ensure first element's value is 7

  // test appending to non-empty list
  head = build_three_node_list(42, 74, 51);
  node* ap_ten = init_node(10);
  append(&head, ap_ten);
  node* four = scan(head, 3);
  REQUIRE(four != NULL);
  REQUIRE(four->data == 10);
  node* ap_ninenine = init_node(99);
  append(&head, ap_ninenine);
  node* five = scan(head, 4);
  REQUIRE(five != NULL);
  REQUIRE(five->data == 99);
}

TEST_CASE("Linked lists: insert data", "[insert data]") {
  node* top = build_three_node_list(30, 20, 10);
  int initial_three[] = { 30, 20, 10 };
  REQUIRE(expect_all(initial_three, 3, &top));
  
  insert_data(&top, 0, 4); // list is now 4, 30, 20, 10
  int vals[] = { 4, 30, 20, 10 };
  REQUIRE(expect_all(vals, 4, &top)); 
  
  insert_data(&top, 2, -8); // list is now 4, 30, -8, 20, 10
  int vals2[] = { 4, 30, -8, 20, 10 };
  REQUIRE(expect_all(vals2, 5, &top));
  
  insert_data(&top, 5, 99); // list is now 4, 30, -8, 20, 10, 99
  int vals3[] = { 4, 30, -8, 20, 10, 99 };
  REQUIRE(expect_all(vals3, 6, &top));
}

TEST_CASE("Linked lists: insert node", "[insert node]") {
  node* top = build_three_node_list(7, 98, -34);
  
  // add at beginning
  node* beginning = init_node(5);
  insert(&top, 0, beginning);
  int vals[] = {5, 7, 98, -34};
  REQUIRE(expect_all(vals, 4, &top));
  
  // add in middle
  node* middle = init_node(20);
  insert(&top, 2, middle);
  int vals2[] = { 5, 7, 20, 98, -34 };
  REQUIRE(expect_all(vals2, 5, &top));

  // add at end
  node* ending = init_node(800);
  insert(&top, 5, ending);
  int vals3[] = { 5, 7, 20, 98, -34, 800 };
  REQUIRE(expect_all(vals3, 6, &top));
}

TEST_CASE("Linked lists: remove", "[remove]") {
  node* top = build_three_node_list(7, 86, 210);
  int vals[] = {7, 86, 210 };
  REQUIRE(expect_all(vals, 3, &top));
  
  // remove start
  remove(&top, 0);
  int vals2[] = {86, 210 };
  REQUIRE(expect_all(vals2, 2, &top));
  
  // reset and remove mid
  top = build_three_node_list(7, 86, 210);
  remove(&top, 1);
  int vals3[] = {7, 210 };
  REQUIRE(expect_all(vals3, 2, &top));

  // reset and remove end
  top = build_three_node_list(7, 86, 210);
  remove(&top, 2);
  int vals4[] = {7, 86 };
  REQUIRE(expect_all(vals4, 2, &top));
}

TEST_CASE("Linked lists: size", "[size]") {
  node* empty = NULL;
  REQUIRE(0 == size(empty));

  node* top = build_three_node_list(8, 30, -43);
  REQUIRE(3 == size(top));
}

TEST_CASE("Linked lists: contains", "[contains]") {
  node* top = build_three_node_list(7, 0, -210);
  REQUIRE(contains(top, -210));
  REQUIRE(contains(top, 0));
  REQUIRE(contains(top, 7));
  REQUIRE_FALSE(contains(top, -21));
  REQUIRE_FALSE(contains(top, 21));
  REQUIRE_FALSE(contains(top, 43));  
}
