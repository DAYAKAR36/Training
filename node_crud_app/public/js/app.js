let queryParameters =
    new URLSearchParams(
        window.location.search
    );

let tableName =
    queryParameters.get("table");

let tableFields = [];

let tableData = [];

window.onload = getData();

function openPopup()
{
    document.getElementById(
        "formContainer"
    ).style.display = "block";
}

function closePopup()
{
    document.getElementById(
        "formContainer"
    ).style.display = "none";
}

function buildForm()
{
    let formBox =
        document.getElementById(
            "formBox"
        );

    formBox.innerHTML = "";

    tableFields.forEach(fieldName =>
    {
        let inputField =
            document.createElement("input");

        inputField.name = fieldName;

        inputField.placeholder = fieldName;

        formBox.appendChild(inputField);

        formBox.appendChild(
            document.createElement("br")
        );
    });

    let saveButton =
        document.createElement("button");

    saveButton.innerText = "Save";

    saveButton.onclick = saveRecord;

    let cancelButton =
        document.createElement("button");

    cancelButton.innerText = "Cancel";

    cancelButton.onclick = closePopup;

    formBox.appendChild(saveButton);

    formBox.appendChild(cancelButton);
}

function getData()
{
    fetch(
        "/getTableDetails?table=" + tableName,
        {
            headers:
            {
                Authorization:
                    "Bearer " +
                    localStorage.getItem("token")
            }
        }
    )

    .then(response => response.json())

    .then(data =>
    {
        if (data.error)
        {
            document.getElementById(
                "tableContainer"
            ).innerText = data.error;

            return;
        }

        tableFields = data.columns;

        tableData = data.rows;

        buildForm();

        renderTable(tableData);
    });
}

function renderTable(rows)
{
    let tableContainer =
        document.getElementById(
            "tableContainer"
        );

    tableContainer.innerHTML = "";

    if (!rows || rows.length === 0)
    {
        tableContainer.innerHTML =
            "No Records";

        return;
    }

    let tableElement =
        document.createElement("table");

    tableElement.border = "1";

    let headerRow =
        document.createElement("tr");

    tableFields.forEach(fieldName =>
    {
        let th =
            document.createElement("th");

        th.innerText = fieldName;

        headerRow.appendChild(th);
    });

    let updateHeader =
        document.createElement("th");

    updateHeader.innerText = "Update";

    headerRow.appendChild(updateHeader);

    let deleteHeader =
        document.createElement("th");

    deleteHeader.innerText = "Delete";

    headerRow.appendChild(deleteHeader);

    tableElement.appendChild(headerRow);

    rows.forEach(row =>
    {
        let tableRow =
            document.createElement("tr");

        tableFields.forEach(fieldName =>
        {
            let td =
                document.createElement("td");

            td.innerText =
                row[fieldName];

            tableRow.appendChild(td);
        });

        let updateCell =
            document.createElement("td");

        let updateButton =
            document.createElement("button");

        updateButton.innerHTML =
            '<i class="bi bi-pencil"></i>';

        updateButton.onclick = () =>
        {
            loadIntoForm(row);
        };

        updateCell.appendChild(updateButton);

        tableRow.appendChild(updateCell);

        let deleteCell =
            document.createElement("td");

        let deleteButton =
            document.createElement("button");

        deleteButton.innerHTML =
            '<i class="bi bi-trash"></i>';

        deleteButton.onclick = () =>
        {
            deleteRecord(row);
        };

        deleteCell.appendChild(deleteButton);

        tableRow.appendChild(deleteCell);

        tableElement.appendChild(tableRow);
    });

    tableContainer.appendChild(tableElement);
}

function loadIntoForm(row)
{
    openPopup();

    document
    .querySelectorAll("#formBox input")
    .forEach(inputField =>
    {
        inputField.value =
            row[inputField.name] ?? "";
    });

    document.getElementById(
        "message"
    ).innerText = "";
}

function resetForm()
{
    document
    .querySelectorAll("#formBox input")
    .forEach(inputField =>
    {
        inputField.value = "";
    });
}

function saveRecord()
{
    let formData = {};

    document
    .querySelectorAll("#formBox input")
    .forEach(inputField =>
    {
        formData[inputField.name] =
            inputField.value.trim();
    });

    fetch(
        "/saveRecord?table=" + tableName,
        {
            method: "POST",

            headers:
            {
                Authorization:
                    "Bearer " +
                    localStorage.getItem("token"),

                "Content-Type":
                    "application/json"
            },

            body: JSON.stringify(formData)
        }
    )

    .then(response => response.text())

    .then(result =>
    {
        document.getElementById(
            "message"
        ).innerText = result;

        if (result.trim() === "SUCCESS")
        {
            getData();

            resetForm();

            closePopup();
        }
    });
}

function deleteRecord(row)
{
    if (!confirm(
        "Are you sure?"
    ))
    {
        return;
    }

    fetch(
        "/deleteRecord?table=" + tableName,
        {
            method: "POST",

            headers:
            {
                Authorization:
                    "Bearer " +
                    localStorage.getItem("token"),

                "Content-Type":
                    "application/json"
            },

            body: JSON.stringify(row)
        }
    )

    .then(response => response.text())

    .then(result =>
    {
        document.getElementById(
            "message"
        ).innerText = result;

        if (result.trim() === "SUCCESS")
        {
            getData();
        }
    });
}
