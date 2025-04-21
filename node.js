const express = require('express');
const multer = require('multer');
const tesseract = require('tesseract.js');
const fs = require('fs');
const path = require('path');

const app = express();
const port = 57838; // Use the specified port

// Configure multer for image file uploads
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, 'uploads/')
  },
  filename: function (req, file, cb) {
    cb(null, Date.now() + path.extname(file.originalname))
  }
});

const upload = multer({ storage: storage });

// Ensure the uploads directory exists
if (!fs.existsSync('uploads')) {
  fs.mkdirSync('uploads');
}

// Endpoint for handling file upload
app.post('/upload', upload.single('file'), (req, res) => {
  const filePath = path.join(__dirname, 'uploads', req.file.filename);

  // Perform OCR on the uploaded image using Tesseract.js
  tesseract.recognize(
    filePath,
    'eng',
    {
      logger: (m) => console.log(m),
    }
  ).then(({ data: { text } }) => {
    console.log('OCR Result: ', text);
    res.json({
      success: true,
      extractedText: text,
    });

    // Optionally, delete the image after processing
    fs.unlinkSync(filePath);
  }).catch(err => {
    console.error('Error processing image: ', err);
    res.status(500).json({ success: false, error: 'Failed to process image.' });
  });
});

// Listen on the specified IP address and port
const host = '0.0.0.0';  // Use '0.0.0.0' to allow connections from any IP address
app.listen(port, host, () => {
  console.log(`Server running on http://35.156.54.176:${port}`);
});
