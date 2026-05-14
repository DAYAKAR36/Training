const express = require("express");
const cors = require("cors");
const path = require("path");

const app = express();
const serverPort = 3000;
const authorization = require("./authorization");

app.use(cors());
app.use(express.json());
app.use(express.static(path.join(__dirname, "public")));

app.get("/getTableDetails", authorization, require("./getTableDetails"));
app.post("/saveRecord", authorization, require("./saveRecord"));
app.post("/deleteRecord", authorization, require("./deleteRecord"));

app.listen(serverPort, () => 
{
  console.log("Server running on http://localhost:" + serverPort);
});