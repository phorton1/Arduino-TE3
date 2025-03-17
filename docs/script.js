// script.js

function removeSidebarSelected() {
    const activeLink = document.querySelector('.sidebar_selected');
    if (activeLink) {
        activeLink.classList.remove('sidebar_selected');
    }
}

function toggleFolderLI(event, li_element) {
    const triangle = li_element.querySelector('span'); // Get the child <span>
    const nestedList = li_element.querySelector('ul'); // Get the child <ul>
    if (triangle.classList.contains('expanded')) {
        triangle.classList.remove('expanded');
        nestedList.style.display = "none";
    } else {
        triangle.classList.add('expanded'); // Add the expanded class
        nestedList.style.display = "block";
    }
}

function loadDataFile(a_element) {
    loadFileAndExpand(a_element.dataset.file);
}

function loadFileAndExpand(filename) {
    ___loadContent(filename);

    const folderLinks = document.querySelectorAll('[data-file]');
    folderLinks.forEach(link => {
        if (link.dataset.file === filename) {
            removeSidebarSelected();
            link.classList.add('sidebar_selected');
            let currentLi = link.parentNode;
            while (currentLi) {
                const triangle = currentLi.querySelector('.triangle');
                if (triangle) {
                    triangle.classList.add('expanded');
                    const nestedList = currentLi.querySelector('ul');
                    if (nestedList) {
                        nestedList.style.display = "block";
                    }
                }
                currentLi = currentLi.parentNode.closest('li');
            }
        }
    });
}

let in_hash = false;

function ___loadContent(filename) {
    if (in_hash) return;
    in_hash = true;

    const contentArea = document.getElementById('content');
    fetch(filename)
        .then(response => {
            if (!response.ok) throw new Error('Network response was not ok');
            return response.text();
        })
        .then(data => {
            contentArea.innerHTML = data;
            updateOnThisPage();

            let hash_string = `#${filename}`;
            console.log("hash_string='" + hash_string + "'");

            if (location.hash !== hash_string) {
                history.pushState({ file: filename }, '', hash_string);
            }
        })
        .catch(error => {
            console.error('There was a problem with the fetch operation:', error);
            contentArea.innerHTML = '<p>Error loading content.</p>';
        })
        .finally(() => {
            in_hash = false; // Reset the flag after loading
        });
}

function updateOnThisPage() {
    const onThisPage = document.getElementById('on-this-page');
    onThisPage.innerHTML = ''; // Clear existing items

    // Get all headings (h2) in the content area
    const headings = document.querySelectorAll('#content h2');

    headings.forEach(heading => {
        const sectionId = heading.id; // Get the ID of the heading
        const sectionText = heading.textContent; // Get the text of the heading

        // Create a new list item with a link to the section
        const listItem = document.createElement('li');
        const link = document.createElement('a');
        link.href = `#${sectionId}`; // Set the href to the section ID
        link.textContent = sectionText; // Set the link text
        link.addEventListener('click', function(e) {
            e.preventDefault(); // Prevent default anchor behavior
            const target = document.getElementById(sectionId);
            if (target) {
                target.scrollIntoView({ behavior: 'smooth' }); // Smooth scroll to the section
            }
        });

        listItem.appendChild(link);
        onThisPage.appendChild(listItem); // Add the list item to the sidebar
    });
}



function handleHashChange() {
    const filename = location.hash.substring(1); // Remove the '#' character
    if (filename) {
        loadFileAndExpand(filename);
    }
}

window.addEventListener('hashchange', handleHashChange);
window.addEventListener('popstate', function(event) {
    if (event.state) {
        loadFileAndExpand(event.state.file);
    } else {
        handleHashChange(); // Handle the case where there's no state
    }
});

function startJS() {
    if (location.hash) {
        handleHashChange();
    } else {
        loadFileAndExpand('home.htm'); // Load default content if no hash
    }
}

// end of script.js