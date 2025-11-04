document.addEventListener("DOMContentLoaded", function() {

    // do stuffs 
    // documentation for adafruit IO : https://github.com/methio/adafruitIO-class
    // documentation for alwan color picker : https://github.com/sefianecho/alwan
    // documentation for Name That Color (NTC) : https://chir.ag/projects/ntc/
    
    // adafruit Setup
    const IO = new AdafruitIO("username", "API_key");
   
    // the code we want to run when the html page is loaded

    // the time between data requests to Adafruit
    const delayBetweenRequest = 5000;

    let FirstFingerHeight = Math.floor(Math.random()*20);

    

    // Faking first finger height
    

    // sending false first finger height on Adafruit
    
    IO.postData("fingers-height", FirstFingerHeight);
   
    // asking the sensor to start collecting data when there is a click on the train button
    const trainButton = document.getElementById("trainButton");
    trainButton.addEventListener("click", function(){
    
    setInterval(function() {
        IO.getData("fingers-height", function(data) {
            // debug data we get from feed
            console.log( `🚚 - Here is your data from ${data.feed}! Latest value is: ${data.json[0].value}`);
            console.log(data.json);
    let FirstFingerHeightDisplay = document.getElementById("FirstFingerHeight");
    FirstFingerHeightDisplay.innerHTML = data.json[0].value
        
});
    },delayBetweenRequest);
    });

    });