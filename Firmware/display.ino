<!DOCTYPE html>
<html>
<head>
  <title>Mechanical Display</title>
  <style>
    body {
      background: #2d3340;
      color: white;
      font-family: sans-serif;
      text-align: center;
    }

    #grid {
      display: grid;
      grid-template-columns: repeat(4, 100px);
      gap: 10px;
      justify-content: center;
      margin-top: 30px;
    }

    .pixel {
      width: 100px;
      height: 100px;
      background: green;
      border: 3px solid black;
      cursor: pointer;
      color: white;
      font-size: 14px;
    }
  </style>
</head>
<body>

  <h1>Mechanical Display</h1>
  <p>Click a pixel to flip it between green and red</p>

  <div id="grid">
    <button class="pixel" onclick="flip(this)">r1c1</button>
    <button class="pixel" onclick="flip(this)">r1c2</button>
    <button class="pixel" onclick="flip(this)">r1c3</button>
    <button class="pixel" onclick="flip(this)">r1c4</button>

    <button class="pixel" onclick="flip(this)">r2c1</button>
    <button class="pixel" onclick="flip(this)">r2c2</button>
    <button class="pixel" onclick="flip(this)">r2c3</button>
    <button class="pixel" onclick="flip(this)">r2c4</button>

    <button class="pixel" onclick="flip(this)">r3c1</button>
    <button class="pixel" onclick="flip(this)">r3c2</button>
    <button class="pixel" onclick="flip(this)">r3c3</button>
    <button class="pixel" onclick="flip(this)">r3c4</button>

    <button class="pixel" onclick="flip(this)">r4c1</button>
    <button class="pixel" onclick="flip(this)">r4c2</button>
    <button class="pixel" onclick="flip(this)">r4c3</button>
    <button class="pixel" onclick="flip(this)">r4c4</button>
  </div>

  <script>
    function flip(button) {
      if (button.style.background == "red") {
        button.style.background = "green";
      } else {
        button.style.background = "red";
      }
    }
  </script>

 

  <script>
    const originalFlip = flip;
    flip = function(button) {
      originalFlip(button);
    };
  </script>

</body>
</html>