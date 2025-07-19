import math

print("\n📐✨ Geometry Calculator ✨📐\n")
print("Choose a calculation:")
print("1️⃣  Area of a rectangle 🟥")
print("2️⃣  Perimeter of a rectangle 📏")
print("3️⃣  Area of a triangle 🔺")
print("4️⃣  Perimeter of a triangle 📐")
print("5️⃣  Area of a circle ⚪")
print("6️⃣  Circumference of a circle 🔵")
print("7️⃣  Area of a square ◼️")
print("8️⃣  Perimeter of a square ⬛")

choice = input("\n👉 Enter a number between 1 and 8: ")

try:
    choice = int(choice)
except ValueError:
    print("❌ Invalid input. Please enter a number between 1 and 8.")
    exit()

if choice == 1:
    b = float(input("🔸 Enter the base: "))
    h = float(input("🔸 Enter the height: "))
    area = b * h
    print(f"✅ The area of the rectangle is: {area}")

elif choice == 2:
    b = float(input("🔸 Enter the base: "))
    h = float(input("🔸 Enter the height: "))
    perimeter = 2 * (b + h)
    print(f"✅ The perimeter of the rectangle is: {perimeter}")

elif choice == 3:
    b = float(input("🔸 Enter the base: "))
    h = float(input("🔸 Enter the height: "))
    area = (b * h) / 2
    print(f"✅ The area of the triangle is: {area}")

elif choice == 4:
    a = float(input("🔸 Enter side A: "))
    b = float(input("🔸 Enter side B: "))
    c = float(input("🔸 Enter side C: "))
    perimeter = a + b + c
    print(f"✅ The perimeter of the triangle is: {perimeter}")

elif choice == 5:
    r = float(input("🔸 Enter the radius: "))
    area = math.pi * r ** 2
    print(f"✅ The area of the circle is: {area:.2f}")

elif choice == 6:
    r = float(input("🔸 Enter the radius: "))
    circumference = 2 * math.pi * r
    print(f"✅ The circumference of the circle is: {circumference:.

