//an item in the list
struct ListNode {
  int _value;
  ListNode * _next;
};

class List {
public:
  //Head of list
  ListNode * _head;
  
  void insertSorted( int val ) ;
  void append (int val);
  void prepend (int val);  
  int lookup( int _value );
  int remove( int val );
  void print();
  List();
  ~List();
};


