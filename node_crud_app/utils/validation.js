function validateTableName(tableName)
{
    const pattern =
        /^[a-zA-Z0-9_]+$/;

    return pattern.test(tableName);
}

module.exports = {
    validateTableName
};
