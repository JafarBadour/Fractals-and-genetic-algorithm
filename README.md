# Fractals-and-genetic-algorithm

## How to run the project without having opencv 

* I have added an executable file to this repository "jafar" without quotes
All you have to do is to run the following command in your terminal
 ```./jafar PICTURE1NAME.EXTENSION  NUMBEROFGENERATIONS``` Where the first argument is the name of the picture on the working directory and
 the second argument is the number of generation to be calculated until you will write 
the output picture to ```Output.jpg```.

* Beware that you will be able to see the progress of the program via terminal
in such a way that every generation it will show you the maximum fitness number of the 
generation and number of this generation to be processed.

## How to run with opencv installed (when editing the code)

* You just have to make sure you have cmake installed and run similar commands that are 
available in this repository. 
* Then when the opencv is compiled everything will workout automatically

## Algorithm 

### Face recognition via cascades

Best explaination for why using cascades is on [realpython](https://realpython.com/face-recognition-with-python/) here are some of the points they have made:
* OpenCV uses machine learning algorithms to search for faces within a picture. Because faces are so complicated, there isn’t one simple test that will tell you if it found a face or not. Instead, there are thousands of small patterns and features that must be matched. The algorithms break the task of identifying the face into thousands of smaller, bite-sized tasks, each of which is easy to solve. These tasks are also called classifiers.

* For something like a face, you might have 6,000 or more classifiers, all of which must match for a face to be detected (within error limits, of course). But therein lies the problem: for face detection, the algorithm starts at the top left of a picture and moves down across small blocks of data, looking at each block, constantly asking, “Is this a face? … Is this a face? … Is this a face?” Since there are 6,000 or more tests per block, you might have millions of calculations to do, which will grind your computer to a halt.

* To get around this, OpenCV uses cascades. What’s a cascade? The best answer can be found in the dictionary: “a waterfall or series of waterfalls.”

* After using the cascades in the xml file: original photo was cloned and
and transformed into gray scale (colors do not help with face recognition but sharp edges do so taking away the colors is crucial)
and then the coordinates of faces centers are given back by an array.
* One face is taking at random (as a circle) and fractale creation begins.
### Fractal

* **Koch snowflake** fractal is very famous and here I have used a special edition of my imagination
using the relation that each circle will have 4 tangent circles
such that the circles wont collide amongst themselves. 

* Given that ratio between new circle radius and old circle radius is \lambda conclude that the biggest ratio that we could possible have is $$\frac{1}{\Phi}$$ which is approximately   


