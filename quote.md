**No Quotes**
- echo hello world: This will output hello world. It's considered as two arguments to echo.

**Double Quotes**
- echo "hello world": This will output hello world. It's considered as one argument to echo.
- echo "hello" "world": This will output hello world. It's considered as two arguments to echo.
- echo "hello""world": This will output helloworld. It's considered as one argument to echo.

**Single Quotes**
- echo 'hello world': This will output hello world. It's considered as one argument to echo.
- echo 'hello' 'world': This will output hello world. It's considered as two arguments to echo.
- echo 'hello''world': This will output helloworld. It's considered as one argument to echo.

**Mixed Quotes**
- echo 'hello' "world": This will output hello world. It's considered as two arguments to echo.
- echo "hello"'world': This will output helloworld. It's considered as one argument to echo.
- echo "'Hello, World!'": This will output 'Hello, World!'. The single quotes are treated as part of the string.
- echo '"Hello, World!"': This will output "Hello, World!". The double quotes are treated as part of the string.
- echo "Hello"'" "'World: This will output Hello World. It's considered as one argument to echo.

**Quotes and Variables**
If you have a variable, say var="world", then:
- echo "hello $var": This will output hello world. The variable gets expanded inside double quotes.
- echo 'hello $var': This will output hello $var. The variable does not get expanded inside single quotes.
- echo "'Hello $var!'": This will output 'Hello World!'.
- echo '"Hello '$var'!"': This will output "Hello World!".

In Bash, arguments with quotes are treated as follows:

- ./test "A B" is considered as one argument, the 3 character string A space B.
- ./test ""A B"" is considered as two arguments, the first being the empty string concatenated with A, and the second being B concatenated with empty string.
- ./test """A B""" is considered as one argument, the empty string concatenated with A space B concatenated with empty string.
- ./test """"A B"""" is considered as two arguments, the first being empty string concatenated with empty string concatenated with A, and the second being B concatenated with empty string concatenated with empty string.

'foo"bar'"baz'quux" will be seen as one argument: foo"barbaz'quux.

**Examples**
bash-3.2$ echo test hi hello
test hi hello

bash-3.2$ echo "test"hi"hello"
testhihello

bash-3.2$ echo "test "hi" hello"
test hi hello

bash-3.2$ echo "test""hi""hello"
testhihello

bash-3.2$ echo "test" "hi" "hello"
test hi hello

bash-3.2$ echo "test"  "hi"  "hello"
test hi hello

bash-3.2$ echo "test"  "hi"  "hello" "|" cat > 1.tmp
test hi hello | cat			<- inside 1.tmp

bash-3.2$ echo "test"'hi'"hello"
testhihello

bash-3.2$ echo "test" 'hi' "hello"
test hi hello

bash-3.2$ echo "test'hi'hello"
test'hi'hello

bash-3.2$ echo "test 'hi' hello"
test 'hi' hello

bash-3.2$ echo "test""'hi' hello"
test'hi' hello

bash-3.2$ echo "test""'hi'""hello"
test'hi'hello

bash-3.2$ echo "t'es't""'hi'""hello"
t'es't'hi'hello