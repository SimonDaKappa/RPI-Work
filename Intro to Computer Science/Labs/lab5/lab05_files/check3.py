import wikimedia
import check2


def ask_query():
    search = input("Enter a place => ")
    images = wikimedia.find_images(search,4)
    if len(images) >= 4:
        check2.twobytwo(images).show()
    else:
        print("Could not find a sufficient number of images")

if __name__ == "__main__":
    ask_query()
    