const express = require('express');
const multer = require('multer');
const tesseract = require('tesseract.js');

const app = express();
const upload = multer({ dest: 'uploads/' });

// Endpoint for image upload
app.post('/upload', upload.single('file'), (req, res) => {
  const imagePath = req.file.path;

  // Run OCR on the uploaded image
  tesseract.recognize(imagePath, 'eng', {
    logger: (m) => console.log(m),
  })
  .then(({ data: { text } }) => {
    res.json({ text: text });  // Send back the recognized text
  })
  .catch((err) => {
    res.status(500).send('Error processing image');
  });
});

app.listen(57838, () => {
  console.log('OCR server running on port 57838');
});
