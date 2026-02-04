class Member:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def __lt__(self, other):
        return self.age < other.age

    def __str__(self):
        return f"name: {self.name}, age: {self.age}"

    def __repr__(self):
        return f"(name: {self.name}, age: {self.age})"


def main():
    members = [Member("조니", 40), Member("실비", 20), Member("나나", 4)]
    members.sort()
    print(members)


if __name__ == "__main__":
    main()
