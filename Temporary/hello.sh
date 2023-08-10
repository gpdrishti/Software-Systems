
#! /bin/bas
#this is a comment 
echo "hello word"

echo $BASH
echo $BASH_VERSION
echo $HOME
echo $PWD

value=mark
echo the name is $value

echo "enter names :"
read name1 name2 name3 
echo "entered names :$name1, $name2, $name3"

read -p 'username:' user_var
read -sp 'password' pass_var
echo "username is" $user_var

read -a names
echo "names are: ${names[0]} ${names[1]}"

count=10
word=a
if[$count -eq 9]
then
  echo"condition is true"
elif[[$word =='a']]
then
echo "condition a is true"
else
  echo"condition is false"
fi

echo -e "enter the name of the file : \c"
read file_name

if[-e $file_name]
then
  echo"$file_name found"
else
  echo"$file_name not found"
fi

