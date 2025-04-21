const express = require('express');
const multer = require('multer');
const tesseract = require('tesseract.js');
const fs = require('fs');
const path = require('path');

const app = express();
const upload = multer({ dest: 'uploads/' });

// Endpoint for image upload
app.post('/upload', upload.single('file'), (req, res) => {
  if (!req.file) {
    return res.status(400).json({ error: 'No file uploaded' });
  }

  const imagePath = req.file.path;

  // Perform OCR
  tesseract.recognize(imagePath, 'eng', {
    logger: m => console.log(m),
  })
  .then(({ data: { text } }) => {
    // Clean up uploaded file
    fs.unlink(imagePath, err => {
      if (err) console.error('Error deleting uploaded file:', err);
    });

    // Send back recognized text
    res.json({ text: text.trim() });
  })
  .catch(err => {
    console.error('OCR error:', err);

    // Clean up on error too
    fs.unlink(imagePath, err => {
      if (err) console.error('Error deleting file after OCR fail:', err);
    });

    res.status(500).json({ error: 'Error processing image' });
  });
});

// IMPORTANT: Bind to all IPs, not just localhost
const PORT = 57838;
app.listen(PORT, '0.0.0.0', () => {
  console.log(`🧠 OCR server running on port ${PORT}`);
});
