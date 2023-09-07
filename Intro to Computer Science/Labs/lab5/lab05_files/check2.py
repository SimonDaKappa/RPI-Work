from PIL import Image
import check2_helper

def twobytwo(imagelist): 
    """Takes a list of images, and resizes the first four to (256,256) and then creates a 512x512 2x2 wallpaper"""
    for i in range(4): # Resizes the first four images
        imagelist[i] = check2_helper.make_square(imagelist[i])
        imagelist[i] = imagelist[i].resize((256,256))
    
    out = Image.new('RGB', (imagelist[0].width + imagelist[1].width, imagelist[0].height + imagelist[2].height ))
    out.paste(imagelist[0], (0, 0))
    out.paste(imagelist[1], (imagelist[0].height, 0))
    out.paste(imagelist[2], (0, imagelist[0].width))
    out.paste(imagelist[3], (imagelist[0].height, imagelist[0].width))
    return out


if __name__ == "__main__":
    imagelist = [Image.open("ca.jpg"),Image.open("im.jpg"),Image.open("hk.jpg"),Image.open("bw.jpg")]
    twobytwo(imagelist).show()


