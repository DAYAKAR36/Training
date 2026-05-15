const connection = require("../config/db");

const {
    validateTableName
} = require("../utils/validation");

function deleteRecord(request, response)
{
    const tableName = request.query.table;

    if (!validateTableName(tableName))
    {
        return response.send("ERROR: Invalid table");
    }

    const row = request.body;

    const keys = Object.keys(row);

    if (keys.length === 0)
    {
        return response.send("ERROR: No data");
    }

    const primaryKey = keys[0];

    const sql =
        "DELETE FROM " +
        tableName +
        " WHERE " +
        primaryKey +
        " = ?";

    connection.query(sql, [row[primaryKey]], (error, results) =>
    {
        if (error)
        {
            return response.send("ERROR: " + error.message);
        }

        response.send(results.affectedRows > 0 ? "SUCCESS" : "FAILED");
    });
}

module.exports = deleteRecord;
