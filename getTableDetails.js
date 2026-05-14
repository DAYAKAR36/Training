// Get Table details

const connection = require("./connection");

function getTableDetails(request, response) 
{
  const tableName = request.query.table;
  if (!tableName || tableName.trim() === "") 
  {
    return response.json({ error: "Please provide Table name" });
  }
  const sql = "SELECT * FROM " + tableName;
  connection.query(sql, (err, results, fields) => 
  {
    if (err) 
    {
      return response.json({ error: err.message });
    }
    const columns = fields.map((field) => field.name);
    const rows = results.map((row) => 
    {
      const obj = {};
      columns.forEach((column) => 
      {
        obj[column] = row[column] !== undefined ? row[column] : "";
      });
      return obj;
    });

    response.json({ columns, rows });
  });
}

module.exports = getTableDetails;