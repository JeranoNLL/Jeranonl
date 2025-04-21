const express = require('express');
const multer = require('multer');
const tesseract = require('tesseract.js');

const app = express();
const upload = multer({ dest: 'uploads/' });

app.post('/upload', upload.single('files[]'), (req, res) => {  // <-- Field name 'files[]'
    if (!req.file) return res.status(400).send('No file uploaded.');
    
    tesseract.recognize(req.file.path, 'eng')
        .then(({ data: { text } }) => res.json({ text }))
        .catch((err) => res.status(500).send('OCR error: ' + err.message));
});

app.listen(57838, () => console.log('OCR server running on port 57838'));
