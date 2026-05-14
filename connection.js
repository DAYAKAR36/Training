const mysql = require("mysql2");

const connection = mysql.createConnection({
  host: "localhost",
  user: "dayakar1",
  password: "Dayakar1@##$$$",
  database: "dbDayakar1"
});

connection.connect((err) => {
  if (err) {
    console.error("DB connection failed:", err.message);
  } else {
    console.log("Connected to MySQL.");
  }
});

module.exports = connection;