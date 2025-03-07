void main()
{
  print("hello world");
  print(3);
  print("3"+"4");
  print(3+4);
  print("3"*4);
  print("");
  //single line comment
  /*
  multi line comment
  */
  int a = 3; //int is a datatype
  double b = 3.5; //double - floating point number
  String c = "hello"; //string - sequence of characters
  bool d = true; //boolean - true or false
  dynamic e = 3; //can take any datatype of value in it
  dynamic f = 3.5; //likewise
  print(a);
  print(b);
  print(c);
  print(d);
  print(a.runtimeType);
  print(b.runtimeType);
  print(c.runtimeType);
  print(d.runtimeType);
  print(e.runtimeType);
  print(f.runtimeType);
  print("");
  String name = "ABC";
  print("My name is $name");
  name = "$name DEF"; //this is string interpolation
  print("My name is $name"); //dollar sign is used while we do string interpolation
  print("");
}