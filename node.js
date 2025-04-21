const express = require('express');  // Import the express module
const multer = require('multer');    // Import multer for handling file uploads
const tesseract = require('tesseract.js');  // Import Tesseract.js for OCR
const cors = require('cors');        // Import CORS for handling cross-origin requests

const app = express();  // Create the express app
const upload = multer({ dest: 'uploads/' });  // Configure multer to save uploads in 'uploads' directory

app.use(cors());  // Enable all CORS requests (allowing all origins)

// Endpoint for image upload
app.post('/upload', upload.single('file'), (req, res) => {  // 'file' is the expected field name
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

// Start the server
app.listen(57838, () => {
  console.log('OCR server running on port 57838');
});
