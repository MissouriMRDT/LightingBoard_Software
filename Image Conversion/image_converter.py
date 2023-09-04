from PIL import Image
import argparse


def getIntfromRGB(rgb):
    red = rgb[0]
    green = rgb[1]
    blue = rgb[2]
    RGBint = (red << 16) + (green << 8) + blue
    return RGBint

def print_image(file_path: str):
    im = Image.open(file_path)

    if im.size != (16, 16):
        raise TypeError("Needs to be 16x16 image")

    im.load()  # required for png.split()

    matrix = []

    # Create a black image mask, and put non alpha pixels from image ontop
    # For neopixels, black is functionally "off"
    rgb_im = Image.new("RGB", im.size, (0, 0, 0))
    rgb_im.paste(im, mask=im.split()[3])  # 3 is the alpha channel

    for x in range(16):
        for y in range(16):
            # As the array operates in a snake pattern we have to
            # switch directions every other row
            if x % 2 != 0:
                y_val = 15 - y
            else:
                y_val = y
            r, g, b = rgb_im.getpixel((x, y_val))
            matrix.append(getIntfromRGB((r, g, b)))

    print(matrix)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--file",
        help="Specify the name of the image to convert",
    )
    args = parser.parse_args()

    print_image(args.file)
