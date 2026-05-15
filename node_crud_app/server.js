require("dotenv").config();

const express = require("express");
const cors = require("cors");
const path = require("path");

const authorization = require("./middleware/authorization");

const getTableDetails = require("./routes/getTableDetails");
const saveRecord = require("./routes/saveRecord");
const deleteRecord = require("./routes/deleteRecord");

const app = express();

app.use(cors());
app.use(express.json());

app.use(express.static(path.join(__dirname, "public")));

app.get("/getTableDetails", authorization, getTableDetails);

app.post("/saveRecord", authorization, saveRecord);

app.post("/deleteRecord", authorization, deleteRecord);

app.listen(process.env.PORT, () =>
{
    console.log(
        "Server running on http://localhost:" +
        process.env.PORT
    );
});
