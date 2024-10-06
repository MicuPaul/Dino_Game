# Dino_Game
A recreation of the popular offline dino chrome game in C++ using the SFML library.


## Dino_Game intended for single player
https://github.com/user-attachments/assets/49f8026a-3283-4187-9cf3-238f0dc0a1a6


I trained a Neural Network AI in order to play the game where I used a Genetic Algorithm with a population of 300
to train the best Neural Network in order to play the Game.<br />
The inputs of the Network are various information about the obstacles. <br />
The inputs also contain the current height of the dino and the speed of the game.<br />
The info about the obstacles are the following:<br />
<br />
-Distance to next obstacle<br />
-Height of the obstacle<br />
-Width of the obstacle<br />
-Height relative to the ground<br /><br />
We have a total of 8 inputs about the obstacles because we give the dinos info<br />
about the closest obstacle and the next one after that.So in total 10 inputs. <br />
<br />
Through trial and error i have also modified the Mutation Rate of the dinos and the<br />
architecture of the NN. In the end I chose 3 hidden layers with 10 neurons each.<br />
The output layer has 3 neurons each reprezenting an action.<br />
The first neuron is the jump action, the second is the duck option and the third <br />
is the running/do nothing action. I applied a softmax activation fucntion on the output<br />
layer in order to choose the action based on probability.<br />
In rest the hidden layers activation function is RelU. That's why some neurons are black<br />
in the NN visualizer because they are 0.<br /><br />

The next generation is created by first slelecting the first 30 best Dinos and with these 30 dinos cross breeding them.<br />
Ann the rest are randomly created. So the next generation includes the previous best 30 dinos<br />
and all the crossbreeding posibilites between these 30 dinos and some random ones at the end.<br />
<br />
The most difficult challange was to get the dinos to duck under the birds. That's why I've implemented a reward system<br />
and a penalty system where the score of each dino is rewarded or penalized based on it's action. Therefor <br />
their fitness would rise or drop.<br />
<br />
There is a small penalty for jumping so they learn faster that just jumping endlessy wont get them far.<br />
And there is a big reward if the duck under the birds.<br />
There is also a small penalty for ducking if it isn't under a bird so they wont duck endlessy.<br />
In the end they have reached the max speed possible after a few hundrer generations and if<br />
I let them they can go endlessly playing the game.<br />
I find this a great success.<br />
<br />



## Dino_Game AI trained with a Genetic Algorithm and visualizing best Dino Neural Network
https://github.com/user-attachments/assets/11d0acb3-3bb8-4b3c-a349-709a4fd4c00d

