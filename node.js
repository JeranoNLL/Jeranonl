const express = require('express');
const multer = require('multer');
const tesseract = require('tesseract.js');
const fs = require('fs');
const path = require('path');

const app = express();
const upload = multer({ dest: 'uploads/' });

// POST /upload - handle file uploads
app.post('/upload', upload.single('file'), (req, res) => {
  const imagePath = req.file.path;

  // Run OCR with Tesseract.js
  tesseract.recognize(imagePath, 'eng', {
    logger: m => console.log(m) // optional: logs progress
  })
  .then(({ data: { text } }) => {
    // Delete the uploaded file after processing
    fs.unlink(imagePath, (err) => {
      if (err) console.error('Failed to delete temp file:', err);
    });

    // Return recognized text as JSON
    res.json({ text: text.trim() });
  })
  .catch(err => {
    console.error('OCR Error:', err);

    // Clean up file even on failure
    fs.unlink(imagePath, (unlinkErr) => {
      if (unlinkErr) console.error('Failed to delete temp file:', unlinkErr);
    });

    res.status(500).json({ error: 'Error processing image' });
  });
});

// Start the server
const PORT = 54381;
app.listen(PORT, () => {
  console.log(`🧠 OCR server running on port ${PORT}`);
});
