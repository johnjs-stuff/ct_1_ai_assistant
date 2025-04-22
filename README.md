# Crafting Academy - Capstone project 1
Crafting Academy Capstone project 1 - AI Assistant with a USB keyboard

It ain't much but it is working. A USB keyboard is used to enter some text for a prompt. The keyboard handler can only cope with lower case characters and minimal punctuation. The entered text is displayed on the small screen of the T-Display as it is typed. For those who make the occasional typo, the backspace key can be used to remove the last entered character. At the press of the Enter/Return key, the entered text is sent as a prompt to the OpenAI API, using a WiFi connection. After OpenAI returns a response the actual message is extracted from the response and displayed on the small screen of the T-Display microcontroller in what can be described as the smallest readable font, at least for my eyesight. Not very useful but proof that it can be done.

Hardware used:
* TTGO Lilygo T-Display
* USB keyboard (Brand "XTime". Refer to image)
* Breadboard power supply (similar to https://www.amazon.com/Magic-shell-Breadboard-Battery-Assortment/dp/B07RVHQB1S)
* 9V battery and connector
* 2 x 10K resistors

Other Setups:
* An account with OpenAI and the ability to create an API key.
  
Notes:
* This only works for my USB keyboard which is branded "XTime". It doesn't work with my wired Apple keyboard or my wired Microsoft keyboard. Other keyboards may or may not work.
* A breadboard power supply is used to provide power for the keyboard. The voltage is set to 5V.
* 2 x 10K pullup resistors are needed for the inputs.
* The MySecrets.h file has to be modified with your network name, network password and OpenAI APIkey.
