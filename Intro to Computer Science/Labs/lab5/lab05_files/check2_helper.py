from PIL import Image

def make_square(image):
    dimensions = image.size
    
    if dimensions[0] > dimensions[1]:
        box = (0,0,dimensions[1],dimensions[1])
        image = image.crop(box)
    elif dimensions[0] < dimensions[1]:
        box = (0,0,dimensions[0],dimensions[0])
        image = image.crop(box)
    return image
  

if __name__ == "__main__":  
    #TESTING    
    im = Image.open("im.jpg")
    im = make_square(im)
    im.show()


