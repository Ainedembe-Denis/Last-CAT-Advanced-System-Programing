# Create and write student records
with open("students.txt", "w") as file:
    file.write("Name: Denis Ainedembe  |  ID: 101  |  Marks: 88.2\n")
    file.write("Name: Olivia Namusoke  |  ID: 102  |  Marks: 74.5\n")
    file.write("Name: Henry Masuuba    |  ID: 103  |  Marks: 94.3\n")

# Read and display student records
with open("students.txt", "r") as file:
    content = file.read()
    print("Student Records:\n")
    print(content)
