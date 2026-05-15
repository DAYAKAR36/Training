const connection =
    require("../config/db");

const {
    validateTableName
} = require("../utils/validation");

function saveRecord(request, response)
{
    const tableName =
        request.query.table;

    if (!validateTableName(tableName))
    {
        return response.send(
            "ERROR: Invalid table"
        );
    }

    const formData =
        request.body;

    const keys =
        Object.keys(formData);

    if (keys.length === 0)
    {
        return response.send(
            "ERROR: No data provided"
        );
    }

    const columns =
        keys.join(", ");

    const placeholders =
        keys.map(() => "?").join(", ");

    const updatePart =
        keys.map(key =>
            key + "=VALUES(" + key + ")"
        ).join(", ");

    const values =
        keys.map(key => formData[key]);

    const sql =
        "INSERT INTO " + tableName +
        " (" + columns + ")" +
        " VALUES (" + placeholders + ")" +
        " ON DUPLICATE KEY UPDATE " +
        updatePart;

    connection.query(
        sql,
        values,
        (error, results) =>
        {
            if (error)
            {
                return response.send(
                    "ERROR: " + error.message
                );
            }

            response.send(
                results.affectedRows > 0
                    ? "SUCCESS"
                    : "FAILED"
            );
        }
    );
}

module.exports = saveRecord;
