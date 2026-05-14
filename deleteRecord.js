const connection = require("./connection");

function deleteRecord(request, response) {
  const tableName = request.query.table;
  const row = request.body;
  const keys = Object.keys(row);

  if (keys.length === 0) {
    return response.send("ERROR: No data provided");
  }

  const pkField = keys[0];
  const sql = "DELETE FROM " + tableName + " WHERE " + pkField + " = ?";

  connection.query(sql, [row[pkField]], (err) => {
    if (err)
    {
		return response.send("ERROR: " + err.message);
	}
    response.send("SUCCESS");
  });
}

module.exports = deleteRecord;