// Authorization

function authorization(request, response, next)
{
    const auth = request.headers["authorization"];

    if (auth == null || !auth.startsWith("Bearer "))
    {
        return response.status(401).json(
        {
            error: "Unauthorized"
        });
    }

    const token = auth.substring(7);

    if (token !== "dayakar_token")
    {
        return response.status(403).json(
        {
            error: "Access Denied"
        });
    }
    next();
}

module.exports = authorization;