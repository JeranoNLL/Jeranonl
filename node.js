const express = require('express');
const multer  = require('multer');
const path = require('path');
const app = express();

const upload = multer({ dest: 'uploads/' });

app.post('/upload', upload.single('file'), (req, res) => {
    console.log('File uploaded:', req.file);
    res.send({ status: 'success', path: req.file.path });
});

app.listen(5000, () => {
    console.log('Uploader running on port 5000');
});
