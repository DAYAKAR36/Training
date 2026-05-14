const connection = require("./connection");

function saveRecord(request, response) {
  const tableName = request.query.table;
  const formData = request.body;
  const keys = Object.keys(formData);

  if (keys.length === 0) {
    return response.send("ERROR: No data provided");
  }

  const columns      = keys.join(", ");
  const placeholders = keys.map(() => "?").join(", ");
  const updatePart   = keys.map((key) => key + " = VALUES(" + key + ")").join(", ");
  const values       = keys.map((key) => formData[key]);

  const sql = "INSERT INTO " + tableName + " (" + columns + ")" + " VALUES (" + placeholders + ")" + " ON DUPLICATE KEY UPDATE " + updatePart;
  connection.query(sql, values, (err) => 
  {
    if (err) 
    {
    	return response.send("ERROR: " + err.message);
    }
    response.send("SUCCESS");
  });
}

module.exports = saveRecord;