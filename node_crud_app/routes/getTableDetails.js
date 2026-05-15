const connection = require("../config/db");

const {
    validateTableName
} = require("../utils/validation");

function getTableDetails(request, response)
{
    const tableName = request.query.table;

    if (!tableName)
    {
        return response.json({
            error: "Please provide table name"
        });
    }

    if (!validateTableName(tableName))
    {
        return response.json({
            error: "Invalid table name"
        });
    }

    const sql = "SELECT * FROM " + tableName;

    connection.query(sql, (error, results, fields) =>
    {
        if (error)
        {
            return response.json({
                error: error.message
            });
        }

        const columns = fields.map(field => field.name);

        const rows = results.map(row =>
        {
            const obj = {};

            columns.forEach(column =>
            {
                obj[column] = row[column] ?? "";
            });

            return obj;
        });

        response.json({
            columns,
            rows
        });
    });
}

module.exports = getTableDetails;
