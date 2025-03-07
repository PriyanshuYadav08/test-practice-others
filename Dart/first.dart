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

  var g = 3; //var is used to declare a variable without specifying the datatype
  //mutable variable
  print(g);

  final h = 3; //final is used to declare a variable which cannot be changed
  //immutable variable
  //h = 4; //this will give an error
  //final variable give runtime error
  print(h);

  const i = 3; //const is used to declare a variable which cannot be changed
  //immutable variable
  //i = 4; //this will give an error
  //const variable give compile time error
  print(i);
  print("");

  final date = DateTime.now();
  print(date);
  print("");

  //Optional Variables
  //Optional variables are those variables which can have a null value
  //or String/int/double/bool value
  String? myName = "huihuihui";
  print(myName);
  int? myAge = 20;
  print(myAge);
  print(myName.runtimeType);
  print(myAge.runtimeType);
  print("");
}