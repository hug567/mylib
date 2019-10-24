import sys

# print
print("hello python world")

# define variable
message = "define and align variable"
print(message)

# assign variable
message="assign variable"
print(message)

# string
print("This is a string")
print('This is also a string')

# string method
name = "Huang xing"
print("string.title(): ", name.title())
print("string.uapper(): ", name.upper())
print("string.lower(): ", name.lower())

# string connet
first_name = "Wu"
last_name = "Sixi"
full_name = first_name + " " + last_name
print("string connect: ", full_name)

# escape character
print("Languages:\n\tPython\n\tC\n\tJavaScript")

# delete trailing space
favorite = "python      "
print("favorite: ", favorite, ".")
print("favorite: ", favorite.rstrip(), ".")
sys.stdout.write("favorite: %s.\n" % favorite.rstrip())





